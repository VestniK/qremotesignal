/**
 * @file xic.cpp
 * @brief Entry point for XML interface compiler
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Jul 2009
 */
#include <stdio.h>

#include <QtCore>
#include <QtXml>
#include <QtXmlPatterns>

#include "interfacedocument.h"
#include "interfacecompiler.h"
#include "argvparser.h"
#include "config.h"

#define HELP_FLAG "help"
#define VERSION_FLAG "version"
#define QT_VERSION_FLAG "qt-version"
#define SERVICE_FLAG "service"
#define CLIENT_FLAG  "client"
#define HEADER_OPTION "header"
#define SOURCE_OPTION "source"

int main(int argc, char *argv[]) {
   // Application Info
   QCoreApplication app(argc,argv);
   app.setApplicationName("XML interface compiler");
   app.setApplicationVersion(VERSION);
   QTextStream out(stdout,QIODevice::WriteOnly);
   QTextStream err(stderr,QIODevice::WriteOnly);
   // Command line options configuration
   ArgvParser conf;
   conf.addFlag(HELP_FLAG,conf.tr("Print this help and exit"),'h');
   conf.addFlag(VERSION_FLAG,conf.tr("Print version information and exit"),'v');
   conf.addFlag(QT_VERSION_FLAG,conf.tr("Print Qt version information"));

   conf.addFlag(SERVICE_FLAG,conf.tr("Create service class"),'s');
   conf.addFlag(CLIENT_FLAG,conf.tr("Create client class"),'c');
   conf.addOption(HEADER_OPTION,conf.tr("Specify output header file"));
   conf.addOption(SOURCE_OPTION,conf.tr("Specify output C++ source file"));
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
      out << conf.tr("Compiled with Qt: %1").arg(QT_VERSION_STR) << endl;
      out << conf.tr("Running with Qt version: %1").arg(qVersion()) << endl;
   }
   if ( conf.flags()[VERSION_FLAG] ) {
      out << conf.tr("%1 version: %2").arg(app.applicationName(),app.applicationVersion()) << endl;
      return 0;
   }
   if ( conf.arguments().isEmpty() ) {
      err << conf.tr("Error: Input file not specified!") << endl;
      out << conf.helpStr();
      return 1;
   }
   // Compile document
   InterfaceDocument inputDoc( conf.arguments().first() );
   InterfaceCompiler compiler(&inputDoc);

   /// @todo move output files to the compiler class.
   QString header( conf.options()[HEADER_OPTION] );
   QString source( conf.options()[SOURCE_OPTION] );
   if ( conf.flags()[SERVICE_FLAG] && conf.flags()[CLIENT_FLAG] ) {
      err << "You should specify service or client flag but not both" << endl;
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
         err << app.tr("Failed to compile interface") << endl;
         return 1;
      }
      if ( !compiler.compileServiceSource() ) {
         err << app.tr("Failed to compile interface") << endl;
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
         err << app.tr("Failed to compile interface") << endl;
         return 1;
      }
      if ( !compiler.compileClientSource() ) {
         err << app.tr("Failed to compile interface") << endl;
         return 1;
      }
   } else {
      err << "You should specify service or client flag but not both" << endl;
      return 1;
   }

   return 0;
}
