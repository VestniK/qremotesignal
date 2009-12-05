/**
 * @file argvparser.h
 * @brief ArgvParser class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Aug 2009
 */
#ifndef ArgvParser_H
#define ArgvParser_H

#include <QtCore>

/**
 * Parses command line and store configuration
 * Require QCoreApplication or QApplication object to be initialized
 */
class ArgvParser: public QObject {
   public:
      explicit ArgvParser(QObject *parent = 0);
      virtual ~ArgvParser() {}

      void addFlag(const QString &name,
                  const QString &desc,
                  const QChar &shortName = QChar());
      void addOption(const QString &name,
                     const QString &desc,
                     const QChar &shortName = QChar(),
                     const QString &defaultVal = QString());

      bool parse();
      const QString &errorMessage() {return mError;}

      QString helpStr() const;
      QString qtVersionStr() const;
      QString versionStr() const;

      const QMap<QString,bool> &flags() const {return mFlags;}
      const QMap<QString,QString> &options() const {return mOptions;}
      const QStringList &arguments() const {return mArguments;}
      const QString &execStr() const {return mExecStr;}
      const QString &executableName() const {return mExecutableName;}
      const QString &appDescription() const {return mAppDescription;}

      void setAppDescription(const QString &val) {mAppDescription = val;}
   private:
      Q_DISABLE_COPY(ArgvParser);

      QMap<QString,bool> mFlags;
      QMap<QString,QString> mOptions;
      QStringList mArguments;
      QString mExecStr;
      QString mExecutableName;
      QString mAppDescription;

      QString mError;

      QMap<QChar,QString> mShortNames;
      QMap<QString,QString> mDescriptions;
};

#endif
