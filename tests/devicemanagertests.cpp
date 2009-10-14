/**
 * @file devicemanagertests.cpp
 * @brief DeviceManager tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 7 Oct 2009
 */
#include <QtCore>
#include <QtTest>

#include <QtDebug>

#include "QRemoteSignal"

class DeviceManagerTests: public QObject {
   Q_OBJECT
   private slots:
      void init() {
         mDevice1.setData("");
         mDevice2.setData("");
         mDevice1.open(QIODevice::ReadWrite);
         mDevice2.open(QIODevice::ReadWrite);
         mDevManager1.setDevice(&mDevice1);
         mDevManager2.setDevice(&mDevice2);
      };

      void cleanup() {
         mDevice1.close();
         mDevice2.close();
      };

      void testReadingAlreadyExistingData() {
         QByteArray msg = "Hello";
         mDevManager2.setDevice(0);

         QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
         mDevManager1.send( msg );

         sendDataToDev2( mDevice1.buffer() );
         QCOMPARE(spy.count() , 0);

         mDevManager2.setDevice(&mDevice2);

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toByteArray() , msg);
      };

      void testSendReceive() {
         QByteArray msg = "Hello";

         QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
         mDevManager1.send( msg );

         sendDataToDev2( mDevice1.buffer() );

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toByteArray() , msg);
      };

      void testRecievePart() {
         QByteArray msg = "Long message";

         QSignalSpy mDevice2ReadyReadSpy(&mDevice2,SIGNAL(readyRead()));
         QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));

         mDevManager1.send( msg );
         int splitPoint = mDevice1.buffer().size()/2;

         sendDataToDev2( mDevice1.buffer().left( splitPoint ) );
         QCOMPARE(mDevice2ReadyReadSpy.count(), 1);
         QCOMPARE(spy.count() , 0);

         sendDataToDev2( mDevice1.buffer().mid( splitPoint ) );
         QCOMPARE(mDevice2ReadyReadSpy.count(), 2);
         // Check that message was splited correctly
         QCOMPARE(mDevice1.buffer() , mDevice2.buffer());
         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toByteArray() , msg);
      };

      void testReceiveMultiple() {
         QByteArray msg1 = "Hello";
         QByteArray msg2 = "World";

         QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
         mDevManager1.send( msg1 );
         mDevManager1.send( msg2 );

         sendDataToDev2( mDevice1.buffer() );

         QCOMPARE(spy.count() , 2);
         QCOMPARE(spy.at(0).at(0).toByteArray() , msg1);
         QCOMPARE(spy.at(1).at(0).toByteArray() , msg2);
      };

      void testReceiveOneAndHalf() {
         QByteArray msg1 = "Hello";
         QByteArray msg2 = "Big World";

         QSignalSpy spy(&mDevManager2,SIGNAL(received(QByteArray)));
         mDevManager1.send( msg1 );
         mDevManager1.send( msg2 );
         int splitPoint = mDevice1.buffer().size() - msg2.size()/2;

         sendDataToDev2( mDevice1.buffer().left(splitPoint) );
         QCOMPARE(spy.count() , 1);
         sendDataToDev2( mDevice1.buffer().mid(splitPoint) );
         // Check that message was splited correctly
         QCOMPARE(mDevice1.buffer() , mDevice2.buffer());
         QCOMPARE(spy.count() , 2);
         QCOMPARE(spy.at(0).at(0).toByteArray() , msg1);
         QCOMPARE(spy.at(1).at(0).toByteArray() , msg2);
      };
   private:
      QBuffer mDevice1,mDevice2;
      qrs::DeviceManager mDevManager1,mDevManager2;

      void sendDataToDev2(const QByteArray& data) {
         qint64 pos = mDevice2.pos();
         mDevice2.write( data );
         mDevice2.seek(pos);
         QTest::qWait(1); // Return to qt event loop to allow it process asincronious signals
      }
};

QTEST_MAIN(DeviceManagerTests)
#include "devicemanagertests.moc"
