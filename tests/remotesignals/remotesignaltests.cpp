/**
 * @file remotesignaltests.cpp
 * @brief QRemoteSignal library tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Aug 2009
 */
#include <QtCore/QObject>
#include <QtTest/QtTest>

#include <QRemoteSignal>

#include "exampleclient.h"
#include "exampleservice.h"

class RemoteSignalTests: public QObject {
   Q_OBJECT
   private slots:
      /// Prepare test environment
      void initTestCase() {
         mServerManager = new qrs::ServicesManager(this);
         mClientManager = new qrs::ServicesManager(this);
         connect(mServerManager,SIGNAL(send(QByteArray)),
                 mClientManager,SLOT(receive(const QByteArray&)));
         connect(mClientManager,SIGNAL(send(QByteArray)),
                 mServerManager,SLOT(receive(const QByteArray&)));
         mClient = new qrs::ExampleClient(mClientManager);
         mService = new qrs::ExampleService(mServerManager);
      }
      /// Cleanup test environment
      void cleanupTestCase() {
      }

      /// Data provider for test of QString sending
      void remoteCallStrTest_data() {
         QTest::addColumn<QString>("param");

         QTest::newRow("Empty string") << "";
         QTest::newRow("one") << "one";
         QTest::newRow("Cyrilic") << "Кирилица";
         QTest::newRow("Xml") << "<root>&amp;</root>";
         QTest::newRow("JSON") << "{\"key1\":\"val1\",\"key2\":{\"subkey1\":\"subval1\"}}";
      }
      /// Test of QString sending
      void remoteCallStrTest() {
         QFETCH(QString,param);
         QSignalSpy spy(mService,SIGNAL(strMethod(QString)));

         mClient->strMethod(param);

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toString() , param);
      }

      /// Data provider for test of int sending
      void remoteCallNumTest_data() {
         QTest::addColumn<quint16>("param");

         QTest::newRow("-1") << quint16(-1);
         QTest::newRow("1") << quint16(1);
         QTest::newRow("0") << quint16(0);
         QTest::newRow("50000") << quint16(50000);
      }
      /// Test of int sending
      void remoteCallNumTest() {
         QFETCH(quint16,param);
         QSignalSpy spy(mService,SIGNAL(intMethod(quint16)));

         mClient->intMethod(param);

         QCOMPARE(spy.count() , 1 );
         QCOMPARE(spy.first().at(0).value<quint16>() , param);
      }

      /// Data provider for mixed type parameters sending test
      void remoteCallMixedTest_data() {
         QTest::addColumn<QString>("str");
         QTest::addColumn<int>("num");

         QTest::newRow("10") << "ten" << 10;
         QTest::newRow("-1") << "minus one" << -1;
      }
      /// Test of mixed type parameters sendind
      void remoteCallMixedTest() {
         QFETCH(QString,str);
         QFETCH(int,num);
         QSignalSpy spy(mService,SIGNAL(mixedMethod(QString,int)));

         mClient->mixedMethod(str,num);

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toString() , str);
         QCOMPARE(spy.first().at(1).toInt() , num);
      }

      /// void signal test
      void remoteCallVoidTest() {
         QSignalSpy spy(mService,SIGNAL(voidMethod()));
         mClient->voidMethod();
         QCOMPARE(spy.count() , 1);
      }

      void serviceSignalsTest_data() {
         QTest::addColumn<bool>("flag");

         QTest::newRow("true") << true;
         QTest::newRow("false") << false;
      }
      /// Service to Client remote call
      void serviceSignalsTest() {
         QFETCH(bool,flag);

         QSignalSpy spy(mClient,SIGNAL(boolSignal(bool)));
         mService->boolSignal(flag);
         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toBool() , flag);
      }

   private:
      qrs::ServicesManager *mServerManager,*mClientManager;
      qrs::ExampleClient *mClient;
      qrs::ExampleService *mService;
};

QTEST_MAIN(RemoteSignalTests);

#include "remotesignaltests.moc"
