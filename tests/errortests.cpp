/**
 * @file errortests.cpp
 * @brief QRemoteSignal library error handling tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Sep 2009
 */
#include <QtCore>
#include <QtTest>

#include "communicationmanager.h"
#include "exampleservice.h"
#include "jsonserializer.h"

#include "message.h"

class ErrorTests: public QObject {
   Q_OBJECT
   private slots:
      /// Prepare test environment
      void initTestCase() {
         mServerManager = new qrs::CommunicationManager;
         mSerializer = new qrs::JsonSerializer(mServerManager);
         mServerManager->setSerializer(mSerializer);
         mService = new qrs::ExampleService(mServerManager);
      }
      /// Cleanup test environment
      void cleanupTestCase() {
         delete mServerManager;
      }

      void errorSignalTest() {
         QSignalSpy spy( mServerManager,SIGNAL(error()) );
         qrs::Message msg;
         msg.setErrorType(qrs::Message::UnknownService);
         msg.setError("test error");

         mServerManager->recieve( mSerializer->serialize(msg) );

         QCOMPARE( spy.count(), 1 );
      }

      void incorrectCallTest_data() {
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
      void incorrectCallTest() {
         QFETCH(QString, service);
         QFETCH(QString, method);
         QFETCH(int, expectedErr);
         QSignalSpy spy( mServerManager,SIGNAL(send(QByteArray)) );

         qrs::Message msg;
         msg.setService(service);
         msg.setMethod(method);
         msg.params().insert("str","test");
         mServerManager->recieve(mSerializer->serialize(msg));
         QCOMPARE( spy.count(), 1 );
         qrs::MessageAP err = mSerializer->deserialize( spy.first().at(0).toByteArray() );
         QVERIFY( err->type() == qrs::Message::Error );
         QCOMPARE( (int)err->errorType(), expectedErr );
      }
   private:
      qrs::CommunicationManager *mServerManager,*mClientManager;
      qrs::ExampleService *mService;
      qrs::JsonSerializer *mSerializer;
};

#include "errortests.moc"

QTEST_MAIN(ErrorTests);
