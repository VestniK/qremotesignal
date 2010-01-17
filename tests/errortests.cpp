/**
* @file errortests.cpp
* @brief QRemoteSignal library error handling tests
*
* @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
* @date 5 Sep 2009
*/
#include <QtCore/QObject>
#include <QtTest/QtTest>

#include <QRemoteSignal>

#include "exampleservice.h"

class ErrorSignalSpy:public QObject {
    Q_OBJECT
    public:
        int count;
        QList<qrs::ServicesManager *> senders;
        QList<qrs::Message::ErrorType> types;
        QList<QString> reasons;

        ErrorSignalSpy(qrs::ServicesManager *obj):count(0) {
            connect(obj,SIGNAL(error(qrs::ServicesManager*, qrs::Message::ErrorType, QString)),
                    this,SLOT(catchSignal(qrs::ServicesManager*, qrs::Message::ErrorType, QString)));
            connect(obj,SIGNAL(clientError(qrs::ServicesManager*, qrs::Message::ErrorType, QString)),
                    this,SLOT(catchSignal(qrs::ServicesManager*, qrs::Message::ErrorType, QString)));
        }
    public slots:
        void catchSignal(qrs::ServicesManager *sender,
                         qrs::Message::ErrorType type,
                         QString reason
                         ) {
            count++;
            senders.append(sender);
            types.append(type);
            reasons.append(reason);
        }
};

class ErrorTests: public QObject {
    Q_OBJECT
    private slots:
        /// Prepare test environment
        void initTestCase() {
            mServerManager = new qrs::ServicesManager;
            mService = new qrs::ExampleService(mServerManager);
        }
        /// Cleanup test environment
        void cleanupTestCase() {
            delete mServerManager;
        }

        void errorSignal() {
            ErrorSignalSpy spy( mServerManager );
            qrs::Message msg;
            QString errorMsg = "test error";
            msg.setErrorType(qrs::Message::UnknownService);
            msg.setError(errorMsg);

            qrs::AbsMessageSerializer *serializer = mServerManager->serializer();
            mServerManager->receive( serializer->serialize(msg) );

            QCOMPARE( spy.count, 1 );
            QCOMPARE( spy.senders[0], mServerManager );
            QCOMPARE( spy.types[0] , qrs::Message::UnknownService );
            QCOMPARE( spy.reasons[0] , errorMsg );
        }

        void incorrectCall_data() {
            QTest::addColumn<QString>("service");
            QTest::addColumn<QString>("method");
            QTest::addColumn<int>("expectedErr");

            QTest::newRow("WrongService") << "Wrong" << "do"
            << (int)qrs::Message::UnknownService;
            QTest::newRow("WrongMethod") << "Example" << "wrong"
            << (int)qrs::Message::IncorrectMethod;
            QTest::newRow("WrongParameter") << "Example" << "intMethod"
            << (int)qrs::Message::IncorrectMethod;
            QTest::newRow("WrongParameter") << "Example" << "intMethod"
            << (int)qrs::Message::IncorrectMethod;
            QTest::newRow("NotEnoughParameters") << "Example" << "mixedMethod"
            << (int)qrs::Message::IncorrectMethod;
        }
        void incorrectCall() {
            QFETCH(QString, service);
            QFETCH(QString, method);
            QFETCH(int, expectedErr);
            QSignalSpy spy( mServerManager,SIGNAL(send(QByteArray)) );
            ErrorSignalSpy errrSpy(mServerManager);

            qrs::Message msg;
            msg.setService(service);
            msg.setMethod(method);
            msg.params().insert("str","test");
            qrs::AbsMessageSerializer *serializer = mServerManager->serializer();

            mServerManager->receive(serializer->serialize(msg));
            QCOMPARE( spy.count(), 1 );
            qrs::MessageAP err = serializer->deserialize( spy.first().at(0).toByteArray() );
            QVERIFY( err->type() == qrs::Message::Error );
            QCOMPARE( (int)err->errorType(), expectedErr );
        }

        void clientErrorSignal_data() {
            QTest::addColumn<QString>("service");
            QTest::addColumn<QString>("method");
            QTest::addColumn<int>("expectedErr");

            QTest::newRow("WrongService") << "Wrong" << "do"
            << (int)qrs::Message::UnknownService;
            QTest::newRow("WrongMethod") << "Example" << "wrong"
            << (int)qrs::Message::IncorrectMethod;
            QTest::newRow("WrongParameter") << "Example" << "intMethod"
            << (int)qrs::Message::IncorrectMethod;
            QTest::newRow("WrongParameter") << "Example" << "intMethod"
            << (int)qrs::Message::IncorrectMethod;
            QTest::newRow("NotEnoughParameters") << "Example" << "mixedMethod"
            << (int)qrs::Message::IncorrectMethod;
        }
        void clientErrorSignal() {
            QFETCH(QString, service);
            QFETCH(QString, method);
            QFETCH(int, expectedErr);
            ErrorSignalSpy spy(mServerManager);

            qrs::Message msg;
            msg.setService(service);
            msg.setMethod(method);
            msg.params().insert("str","test");
            qrs::AbsMessageSerializer *serializer = mServerManager->serializer();

            mServerManager->receive(serializer->serialize(msg));
            QCOMPARE( spy.count, 1 );
            QCOMPARE( (int)spy.types[0] , expectedErr );
        }
    private:
        qrs::ServicesManager *mServerManager,*mClientManager;
        qrs::ExampleService *mService;
};

#include "errortests.moc"

QTEST_MAIN(ErrorTests);
