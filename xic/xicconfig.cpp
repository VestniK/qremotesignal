/**
 * @file xicconfig.cpp
 * @brief XicConfig class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Aug 2009
 */
#include "xicconfig.h"

XicConfig::XicConfig(QObject *parent):QObject(parent) {
   mError = "";
}

void XicConfig::addFlag(const QString& name,
                   const QString& desc,
                   const QChar& shortName) {
   mFlags.insert(name,false);
   mShortNames.insert(shortName,name);
   mDescriptions.insert(name,desc);
}

void XicConfig::addOption(const QString& name,
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
bool XicConfig::parse() {
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

QString XicConfig::getHelpStr() const {
   QString res;
   QTextStream out(&res,QIODevice::WriteOnly);
   out << qApp->applicationName() << endl;
   out << "\t" << mExecutableName << " [options] interface.xml" << endl;
   out << endl;
   out << tr("Options:") << endl;
   foreach ( QString name, mDescriptions.keys() ) {
      out << "\t--" << name;
      QChar shortName = mShortNames.key(name);
      if ( shortName != QChar() ) {
         out << ", -" << shortName;
      }
      if ( mOptions.contains(name) ) {
         out << " " << name;
      }
      out << "\t\t" << mDescriptions[name] << endl;
   }
   return res;
}
