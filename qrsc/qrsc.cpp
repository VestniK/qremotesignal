/**
 * @file qrsc.cpp
 * @brief Entry point for QRemoteSignal interface compiler
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Jul 2009
 */
#include <cstdio>

#include <QtCore/QTextStream>
#include <QtCore/QString>
#include <QtCore/QCoreApplication>

#include "interfacedocument.h"
#include "interfacecompiler.h"
#include "argvparser.h"
#include "config.h"

const QString HELP_FLAG = "help";
const QString VERSION_FLAG = "version";
const QString QT_VERSION_FLAG = "qt-version";
const QString SERVICE_FLAG = "service";
const QString CLIENT_FLAG = "client";
const QString HEADER_OPTION = "header";
const QString SOURCE_OPTION = "source";
const QString UPDATE_OPTION = "update";

int main(int argc, char *argv[]) {
   // Application Info
   QCoreApplication app(argc,argv);

   QString locale = QLocale::system().name();
   QTranslator translator;
   translator.load(QString("qrsc_") + locale,TRANSLATIONS_DIR);
   app.installTranslator(&translator);

   ArgvParser conf;
   app.setApplicationName(conf.tr("QRemoteSignal interface compiler"));
   app.setApplicationVersion(VERSION);
   QTextStream out(stdout,QIODevice::WriteOnly);
   QTextStream err(stderr,QIODevice::WriteOnly);
   // Command line options configuration
   conf.setAppDescription(conf.tr(
       "QRemoteSignal interface compiler. Creates client or service source "
       "files from interface XML description. Only one of the --%1 or --%2 "
       " flags should be specified but not both.").arg(SERVICE_FLAG).arg(CLIENT_FLAG)
   );
   conf.addUsageDescription(conf.tr("--%1|--%2 [OPTIONS] INTERFACE")
                                .arg(SERVICE_FLAG)
                                .arg(CLIENT_FLAG));
   conf.addUsageDescription(conf.tr("--%1 SOURCE DEST")
                                .arg(UPDATE_OPTION));
   conf.addFlag(HELP_FLAG,conf.tr("Print this help and exit."),'h');
   conf.addFlag(VERSION_FLAG,conf.tr("Print version information and exit."),'v');
   conf.addFlag(QT_VERSION_FLAG,conf.tr("Print Qt version information and exit."));

   conf.addFlag(SERVICE_FLAG,conf.tr("Create service class."),'s');
   conf.addFlag(CLIENT_FLAG,conf.tr("Create client class."),'c');
   conf.addOption(UPDATE_OPTION,
                  conf.tr("SOURCE DEST"),
                  conf.tr("Update interface file of the format used by the "
                          "library version 0.6.0 and earlier to the current "
                          "version of the interface description file format."),
                  'u');
   conf.addOption(HEADER_OPTION,
                  conf.tr("DEST_HEADER"),
                  conf.tr("Specify output header file."));
   conf.addOption(SOURCE_OPTION,
                  conf.tr("DEST_CPP"),
                  conf.tr("Specify output C++ source file."));
   if ( ! conf.parse() ) {
      err << conf.errorMessage() << endl;
      out << conf.helpStr();
      return 1;
   }
   // Print info if requested
   if ( conf.flags()[HELP_FLAG] ) {
      out << conf.helpStr();
      return 0;
   }
   if ( conf.flags()[QT_VERSION_FLAG] ) {
      out << conf.qtVersionStr();
      return 0;
   }
   if ( conf.flags()[VERSION_FLAG] ) {
      out << conf.versionStr();
      return 0;
   }

    if ( conf.arguments().isEmpty() ) {
        if ( conf.options()[UPDATE_OPTION].isEmpty() ) {
            err << conf.tr("Error: Input file not specified!") << endl;
        } else {
            err << conf.tr("Error: Destination file not specified!") << endl;
        }
        out << conf.helpStr();
        return 1;
    }

   // Update document
   if ( ! conf.options()[UPDATE_OPTION].isEmpty() ) {
      InterfaceDocument inputDoc( conf.options()[UPDATE_OPTION] );
      QFile out(conf.arguments().first());
      out.open(QIODevice::WriteOnly | QIODevice::Text);
      inputDoc.getIODevice()->seek(0);
      out.write( inputDoc.getIODevice()->readAll() );
      return 0;
   }

   InterfaceDocument inputDoc( conf.arguments().first() );
   if ( ! inputDoc.isValid() ) {
      err << inputDoc.error() << endl;
      return 1;
   }
   // Compile document
   InterfaceCompiler compiler(&inputDoc);

   /// @todo move output files to the compiler class.
   QString header = conf.options()[HEADER_OPTION];
   QString source = conf.options()[SOURCE_OPTION];
   if ( conf.flags()[SERVICE_FLAG] && conf.flags()[CLIENT_FLAG] ) {
      err << conf.tr("You should specify --%1 or --%2 flag but not both!")
                 .arg(SERVICE_FLAG).arg(CLIENT_FLAG) << endl;
      return 1;
   }
   if ( conf.flags()[SERVICE_FLAG] ) {
      if ( ! header.isEmpty() ) {
         inputDoc.setServiceHeader(header);
      }
      if ( ! source.isEmpty() ) {
         inputDoc.setServiceSource(source);
      }
      if ( !compiler.compileServiceHeader() ) {
         err << app.tr("Failed to compile the interface!") << endl;
         return 1;
      }
      if ( !compiler.compileServiceSource() ) {
         err << app.tr("Failed to compile the interface!") << endl;
         return 1;
      }
   } else if ( conf.flags()[CLIENT_FLAG] ) {
      if ( ! header.isEmpty() ) {
         inputDoc.setClientHeader(header);
      }
      if ( ! source.isEmpty() ) {
         inputDoc.setClientSource(source);
      }
      if ( !compiler.compileClientHeader() ) {
         err << app.tr("Failed to compile the interface!") << endl;
         return 1;
      }
      if ( !compiler.compileClientSource() ) {
         err << app.tr("Failed to compile the interface!") << endl;
         return 1;
      }
   } else {
      err << app.tr("You should specify --%1 or --%2 flag!")
                .arg(SERVICE_FLAG)
                .arg(CLIENT_FLAG) << endl;
      return 1;
   }

   return 0;
}
