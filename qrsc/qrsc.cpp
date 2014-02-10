/**
 * @file qrsc.cpp
 * @brief Entry point for QRemoteSignal interface compiler
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Jul 2009
 */
#include <cstdio>

#include <QtCore/QtGlobal>
#include <QtCore/QDebug>
#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QCoreApplication>
#include <QtCore/QTranslator>

#include "interfacedocument.h"
#include "interfacecompiler.h"
#include "argvparser.h"
#include "config.h"

namespace cmd {
const QString service = "service";
const QString cleint = "client";
const QString header = "header";
const QString source = "source";
const QString update = "update";
}

ArgvConf qrscArgConf = {
    QT_TRANSLATE_NOOP("ArgvParser", "QRemoteSignal interface compiler"),
    VERSION,
    QT_TRANSLATE_NOOP(
        "ArgvParser",
        "QRemoteSignal interface compiler. Creates client or service source "
        "files from interface XML description. Only one of the --service or "
        "--client flags should be specified but not both."
    )
};

int main(int argc, char *argv[])
{
    // Application Info
    QCoreApplication app(argc,argv);

    QString locale = QLocale::system().name();
    QTranslator translator;
    QString i18nFile = QString("qrsc%1-%2").arg(VERSION_MAJOR_NUMBER).arg(locale);
    if (!translator.load(i18nFile,TRANSLATIONS_DIR))
        translator.load(i18nFile,app.applicationDirPath()+"/../share/i18n");
    app.installTranslator(&translator);

    QTextStream out(stdout,QIODevice::WriteOnly);
    QTextStream err(stderr,QIODevice::WriteOnly);
    ArgvParser conf(qrscArgConf, &out, &err);
    // Command line options configuration
    conf.addUsageDescription(ArgvParser::tr("--%1|--%2 [OPTIONS] INTERFACE")
        .arg(cmd::service)
        .arg(cmd::cleint)
    );
    conf.addUsageDescription(ArgvParser::tr("--%1 SOURCE DEST")
        .arg(cmd::update)
    );

    conf.addFlag(cmd::service,ArgvParser::tr("Create service class."),cmd::service[0]);
    conf.addFlag(cmd::cleint,ArgvParser::tr("Create client class."),cmd::cleint[0]);
    conf.addOption(
        cmd::update,
        ArgvParser::tr("SOURCE DEST"),
        ArgvParser::tr(
            "Update interface file of the format used by the "
            "library version 0.6.0 and earlier to the current "
            "version of the interface description file format."
        ),
        cmd::update[0]
    );
    conf.addOption(
        cmd::header,
        ArgvParser::tr("DEST_HEADER"),
        ArgvParser::tr("Specify output header file.")
    );
    conf.addOption(
        cmd::source,
        ArgvParser::tr("DEST_CPP"),
        ArgvParser::tr("Specify output C++ source file.")
    );
    if (!conf.parse())
        return 1;
    // Print info if requested
    if (conf.handleHelp())
        return 0;

    if (conf.arguments().isEmpty()) {
        if ( conf.options()[cmd::update].isEmpty() )
            err << ArgvParser::tr("Error: Input file not specified!") << endl;
        else
            err << ArgvParser::tr("Error: Destination file not specified!") << endl;
        conf.printHelp();
        return 1;
    }

    // Update document
    if (!conf.options()[cmd::update].isEmpty()) {
        InterfaceDocument inputDoc(conf.options()[cmd::update]);
        QFile out(conf.arguments().first());
        out.open(QIODevice::WriteOnly | QIODevice::Text);
        inputDoc.getIODevice()->seek(0);
        out.write( inputDoc.getIODevice()->readAll() );
        return 0;
    }

    InterfaceDocument inputDoc(conf.arguments().first());
    if (!inputDoc.isValid()) {
        err << inputDoc.error() << endl;
        return 1;
    }
    // Compile document
    InterfaceCompiler compiler(&inputDoc);

    /// @todo move output files to the compiler class.
    QString header = conf.options()[cmd::header];
    QString source = conf.options()[cmd::source];
    if (conf.flags()[cmd::service] && conf.flags()[cmd::cleint]) {
        err << ArgvParser::tr("You should specify --%1 or --%2 flag but not both!")
            .arg(cmd::service).arg(cmd::cleint) << endl;
        return 1;
    }
    if (conf.flags()[cmd::service]) {
        if (!header.isEmpty())
            inputDoc.setServiceHeader(header);
        if (!source.isEmpty())
            inputDoc.setServiceSource(source);
        if (!compiler.compileServiceHeader()) {
            err << QCoreApplication::tr("Failed to compile the interface!") << endl;
            return 1;
        }
        if (!compiler.compileServiceSource()) {
            err << QCoreApplication::tr("Failed to compile the interface!") << endl;
            return 1;
        }
    } else if (conf.flags()[cmd::cleint]) {
        if (!header.isEmpty()) {
            inputDoc.setClientHeader(header);
        }
        if (!source.isEmpty()) {
            inputDoc.setClientSource(source);
        }
        if (!compiler.compileClientHeader()) {
            err << QCoreApplication::tr("Failed to compile the interface!") << endl;
            return 1;
        }
        if (!compiler.compileClientSource()) {
            err << QCoreApplication::tr("Failed to compile the interface!") << endl;
            return 1;
        }
    } else {
        err << QCoreApplication::tr("You should specify --%1 or --%2 flag!")
            .arg(cmd::service)
            .arg(cmd::cleint) << endl;
        return 1;
    }

    return 0;
}
