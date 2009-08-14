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
      const QString& getErrorMessage() {return mError;};

      QString getHelpStr() const;

      const QMap<QString,bool>& getFlags() const {return mFlags;};
      const QMap<QString,QString>& getOptions() const {return mOptions;};
      const QStringList& getArguments() const {return mArguments;};
      const QString& getExecStr() const {return mExecStr;};
      const QString& getExecutableName() const {return mExecutableName;};

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
