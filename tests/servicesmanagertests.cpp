/**
 * @file servicesmanagertests.cpp
 * @brief ServicesManager class tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Nov 2009
 */
#include <QtTest/QtTest>
#include <QtCore/QObject>
#include <QtCore/QBuffer>

#include <QRemoteSignal>

#include "exampleservice.h"
#include "exampleclient.h"

class ServicesManagerTests:public QObject {
   Q_OBJECT
   private slots:

      /// Getting raw message representing voidMethod remote call
      void initTestCase() {
         mManager = new qrs::ServicesManager;
         qrs::ExampleClient *client = new qrs::ExampleClient(mManager);

         QBuffer dev;
         dev.open(QIODevice::ReadWrite);
         mManager->addDevice(&dev);

         client->voidMethod();
         mRawMsg = dev.data();
         delete mManager;
      }

      void init() {
         mManager = new qrs::ServicesManager;
         mService = new qrs::ExampleService(mManager);
      }

      void cleanup() {
         delete mManager;
      }

      void testAddDevice() {
         QBuffer dev;
         QCOMPARE(mManager->devicesCount() , 0);
         mManager->addDevice(&dev);
         QCOMPARE(mManager->devicesCount() , 1);
      }

      void testUsingDevice() {
         QBuffer dev;
         QSignalSpy spy(mService,SIGNAL(voidMethod()));

         dev.open(QIODevice::ReadWrite);
         mManager->addDevice(&dev);
         // Sending message to dev
         QVERIFY( dev.data().isEmpty() );
         mService->boolSignal(true);
         QVERIFY( ! dev.data().isEmpty() );
         // Receiving message from dev
         QCOMPARE(spy.count() , 0);
         sendMsgToDev(&dev, mRawMsg );
         QCOMPARE(spy.count() , 1);
      }

      void testUsingManyDevices() {
         QBuffer dev1;
         QBuffer dev2;
         QSignalSpy spy(mService,SIGNAL(voidMethod()));

         dev1.open(QIODevice::ReadWrite);
         dev2.open(QIODevice::ReadWrite);
         mManager->addDevice(&dev1);
         mManager->addDevice(&dev2);
         // Sending message
         QVERIFY( dev1.data().isEmpty() );
         QVERIFY( dev2.data().isEmpty() );
         mService->boolSignal(true);
         QVERIFY( ! dev1.data().isEmpty() );
         QVERIFY( ! dev2.data().isEmpty() );
         QCOMPARE(dev1.data() , dev2.data());
         // Receiving message from dev1
         QCOMPARE(spy.count() , 0);
         sendMsgToDev(&dev1, mRawMsg );
         QCOMPARE(spy.count() , 1);
         // Receiving message from dev2
         sendMsgToDev(&dev2, mRawMsg );
         QCOMPARE(spy.count() , 2);
      }

      void testSendWithoutSerializer() {
         QBuffer dev;
         dev.open(QIODevice::ReadWrite);
         mManager->setSerializer(0);
         mManager->addDevice(&dev);
         // Sending message to dev
         QVERIFY( dev.data().isEmpty() );
         mService->boolSignal(false);
         QVERIFY( dev.data().isEmpty() );
      }

      void testReceiveWithoutSerializer() {
         QBuffer dev;
         dev.open(QIODevice::ReadWrite);
         mManager->setSerializer(0);
         mManager->addDevice(&dev);
         mManager->receive("some data");
         // There shouldn't be any segmantation faults here
      }

      void testDeleteDevice() {
         QSignalSpy spy(mService,SIGNAL(voidMethod()));
         QBuffer dev;
         QBuffer *tmpDev = new QBuffer();

         dev.open(QIODevice::ReadWrite);
         QCOMPARE(mManager->devicesCount() , 0);
         mManager->addDevice(&dev);
         mManager->addDevice(tmpDev);
         QCOMPARE(mManager->devicesCount() , 2);
         delete tmpDev;
         QCOMPARE(mManager->devicesCount() , 1);
         // Checking that device cleanup was made correctly and message can be
         // sent using dev.
         QCOMPARE(spy.count() , 0);
         mService->boolSignal(false);
         QVERIFY( !dev.data().isEmpty() );
         sendMsgToDev(&dev, mRawMsg );
         QCOMPARE(spy.count() , 1);
      }
   private:
      qrs::ServicesManager *mManager;
      qrs::ExampleService *mService;
      QByteArray mRawMsg;

      void sendMsgToDev(QIODevice *dev, const QByteArray &msg) {
         qint64 pos = dev->pos();
         dev->write( msg );
         dev->seek(pos);
         // Return to qt event loop to allow it process asincronious signals
         QTest::qWait(1);
      }
};

QTEST_MAIN(ServicesManagerTests);

#include "servicesmanagertests.moc"
