/**
 * @file xicconfig.h
 * @brief XicConfig class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Aug 2009
 */
#ifndef XicConfig_H
#define XicConfig_H

#include <QtCore>

/**
 * Parses command line and store configuration
 * Require QCoreApplication or QApplication object to be initialized
 */
class XicConfig: public QObject {
   public:
      XicConfig(QObject *parent = 0);
      virtual ~XicConfig() {};

      void addFlag(const QString& name,
                  const QString& desc,
                  const QChar& shortName = QChar());
      void addOption(const QString& name,
                     const QString& desc,
                     const QChar& shortName = QChar(),
                     const QString& defaultVal = QString());

      bool parse();
      const QString& errorMessage() {return mError;};

      QString helpStr() const;

      const QMap<QString,bool>& flags() const {return mFlags;};
      const QMap<QString,QString>& options() const {return mOptions;};
      const QStringList& arguments() const {return mArguments;};
      const QString& execStr() const {return mExecStr;};
      const QString& executableName() const {return mExecutableName;};

   private:
      QMap<QString,bool> mFlags;
      QMap<QString,QString> mOptions;
      QStringList mArguments;
      QString mExecStr;
      QString mExecutableName;

      QString mError;

      QMap<QChar,QString> mShortNames;
      QMap<QString,QString> mDescriptions;
};

#endif
