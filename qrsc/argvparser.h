/**
 * @file argvparser.h
 * @brief ArgvParser class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Aug 2009
 */
#ifndef ArgvParser_H
#define ArgvParser_H

#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>
#include <QtCore/QList>

struct ArgvConf {
    const char *name;
    const char *version;
    const char *description;
};

class QTextStream;

/**
 * Parses command line and store configuration
 * Require QCoreApplication or QApplication object to be initialized
 */
class ArgvParser {
    Q_DECLARE_TR_FUNCTIONS(ArgvParser)
    public:
        ArgvParser(const ArgvConf &conf, QTextStream *out, QTextStream *err);
        virtual ~ArgvParser() {}

        void addFlag(const QString &name,
                     const QString &desc,
                     const QChar &shortName = QChar());
        void addOption(const QString &name,
                       const QString &paramName,
                       const QString &desc,
                       const QChar &shortName = QChar(),
                       const QString &defaultVal = QString());

        bool parse();
        bool handleHelp();

        QString helpStr() const;
        QString qtVersionStr() const;
        QString versionStr() const;

        const QMap<QString,bool> &flags() const {return mFlags;}
        const QMap<QString,QString> &options() const {return mOptions;}
        const QStringList &arguments() const {return mArguments;}
        const QString &execStr() const {return mExecStr;}
        const QString &executableName() const {return mExecutableName;}
        const QString &appDescription() const {return mAppDescription;}

        void addUsageDescription(const QString &val) {mUsageDescriptions.append(val);};
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
        QList<QString> mUsageDescriptions;
        QTextStream *mOut;
        QTextStream *mErr;
};

#endif
