/**
 * @file libtests.cpp
 * @brief QRemoteSignal library tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Aug 2009
 */
#include <QtCore>
#include <QtTest>

#include "comunicationmanager.h"
#include "exampleclient.h"
#include "exampleservice.h"

Q_DECLARE_METATYPE(QVector<int>);

class RemoteSignalTests: public QObject {
   Q_OBJECT
   private slots:
      /// Prepare test environment
      void initTestCase() {
         serverManager = new qrs::ComunicationManager;
         clientManager = new qrs::ComunicationManager;
         connect(serverManager,SIGNAL(send(QString)),
                 clientManager,SLOT(recieve(const QString&)));
         connect(clientManager,SIGNAL(send(QString)),
                 serverManager,SLOT(recieve(const QString&)));
         client = new qrs::ExampleClient(clientManager);
         service = new qrs::ExampleService(serverManager);
      }
      /// Cleanup test environment
      void cleanupTestCase() {
         delete serverManager;
         delete clientManager;
      }

      /// Data provider for test of QString sending
      void remoteCallStrTest_data() {
         QTest::addColumn<QString>("param");

         QTest::newRow("Empty string") << "";
         QTest::newRow("one") << "one";
         QTest::newRow("Cyrilic") << "Кирилица";
         QTest::newRow("Xml") << "<root>&amp;</root>";
      }
      /// Test of QString sending
      void remoteCallStrTest() {
         QFETCH(QString,param);
         QSignalSpy spy(service,SIGNAL(strMethod(QString)));

         client->strMethod(param);

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toString() , param);
      }

      /// Data provider for test of int sending
      void remoteCallIntTest_data() {
         QTest::addColumn<int>("param");

         QTest::newRow("-1") << -1;
         QTest::newRow("1") << 1;
         QTest::newRow("0") << 0;
         QTest::newRow("70000") << 70000;
      }
      /// Test of int sending
      void remoteCallIntTest() {
         QFETCH(int,param);
         QSignalSpy spy(service,SIGNAL(intMethod(int)));

         client->intMethod(param);

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toInt() , param);
      }

      /// Test of QVector of int sending
      void remoteCallVectorIntTest() {
         qRegisterMetaType< QVector<int> >();
         QVector<int> param;
         param << 1 << 2 << 6;
         QSignalSpy spy(service,SIGNAL(intVectorMethod(QVector<int>)));

         client->intVectorMethod(param);

         QCOMPARE(spy.count() , 1);
         QVERIFY( spy.first().at(0).canConvert< QVector<int> >() );
         QVector<int> ret = spy.first().at(0).value< QVector<int> >();
         for (int i=0; i<ret.size(); i++) {
            qDebug("[%d]=\t%d",i,ret[i]);
         }
         QCOMPARE(ret.size(), param.size());
         for (int i=0; i<param.size(); i++) {
            QCOMPARE(ret[i], param[i]);
         }
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
         QSignalSpy spy(service,SIGNAL(mixedMethod(QString,int)));

         client->mixedMethod(str,num);

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toString() , str);
         QCOMPARE(spy.first().at(1).toInt() , num);
      }

   private:
      qrs::ComunicationManager *serverManager,*clientManager;
      qrs::ExampleClient *client;
      qrs::ExampleService *service;
};

QTEST_MAIN(RemoteSignalTests);

#include "remotesignaltests.moc"
