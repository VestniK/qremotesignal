/**
 * @file argvparser.cpp
 * @brief ArgvParser class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Aug 2009
 */
#include "argvparser.h"

ArgvParser::ArgvParser(QObject *parent):QObject(parent) {
   mError = "";
}

void ArgvParser::addFlag(const QString& name,
                   const QString& desc,
                   const QChar& shortName) {
   mFlags.insert(name,false);
   mShortNames.insert(shortName,name);
   mDescriptions.insert(name,desc);
}

void ArgvParser::addOption(const QString& name,
                   const QString& desc,
                   const QChar& shortName,
                   const QString& defaultVal ) {
   mOptions.insert(name,defaultVal);
   mShortNames.insert(shortName,name);
   mDescriptions.insert(name,desc);
}

/**
 * Require QCoreApplication or QApplication to be initialized
 */
bool ArgvParser::parse() {
   QStringList args = qApp->arguments();
   mExecStr = args[0];
   QFileInfo executableInfo(mExecStr);
   mExecutableName = executableInfo.baseName();
   int i = 1; // args[0] is application itself
   while ( i < args.size() ) {
      QString arg = args[i];
      i++;

      QString name;
      if ( arg.startsWith("--") ) {
         name = arg.mid(2);
      } else {
         if ( arg.startsWith("-") ) {
            name = mShortNames[arg.at(1)];
         } else {
            mArguments.append(arg);
            continue;
         }
      }
      if ( mFlags.contains(name) ) {
         mFlags[name] = true;
         continue;
      }
      if ( mOptions.contains(name) ) {
         if ( i >= args.size() ) {
            mError = tr("Option %1 require a value").arg(arg);
            return false;
         }
         if ( args[i].startsWith('-') ) {
            mError = tr("Option %1 require a value").arg(arg);
            return false;
         }
         mOptions[name] = args[i];
         i++;
         continue;
      }
      mError = tr("Unknown option: %1").arg(arg);
      return false;
   }
   return true;
}

QString ArgvParser::helpStr() const {
   QString res;
   QTextStream out(&res,QIODevice::WriteOnly);
   /// @todo store " [options] interface.xml" in some custumizable variable
   out << tr("Usage: ") << mExecutableName << " [options] interface.xml" << endl;
   out << endl;
   if ( ! mAppDescription.isEmpty() ) {
      out << mAppDescription << endl;
      out << endl;
   }
   out << tr("Options:") << endl;
   foreach ( QString name, mDescriptions.keys() ) {
      out << "\t";
      QChar shortName = mShortNames.key(name);
      if ( shortName != QChar() ) {
         out << "-" << shortName << ", ";
      }
      out << "--" << name;
      if ( mOptions.contains(name) ) {
         out << " " << name;
      }
      out << "\t\t" << mDescriptions[name] << endl;
   }
   return res;
}

QString ArgvParser::qtVersionStr() const {
   QString res;
   QTextStream out(&res,QIODevice::WriteOnly);
   out << tr("Compiled with Qt: %1").arg(QT_VERSION_STR) << endl;
   out << tr("Running with Qt version: %1").arg(qVersion()) << endl;
   return res;
}

QString ArgvParser::versionStr() const {
   QString res;
   QTextStream out(&res,QIODevice::WriteOnly);
   out << mExecutableName << " ("
       << qApp->applicationName()
       << ") " << qApp->applicationVersion()
       << endl;
   return res;
}
