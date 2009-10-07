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
         dev1.setData("");
         dev2.setData("");
         dev1.open(QIODevice::ReadWrite);
         dev2.open(QIODevice::ReadWrite);
         manager1.setDevice(&dev1);
         manager2.setDevice(&dev2);
      };

      void cleanup() {
         dev1.close();
         dev2.close();
      };

      void testSendReceive() {
         QByteArray msg = "Hello";

         QSignalSpy spy(&manager2,SIGNAL(messageReceived(QByteArray)));
         manager1.sendMessage( msg );

         sendDataToDev2( dev1.buffer() );

         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toByteArray() , msg);
      };

      void testRecievePart() {
         QByteArray msg = "Long message";

         QSignalSpy dev2ReadyReadSpy(&dev2,SIGNAL(readyRead()));
         QSignalSpy spy(&manager2,SIGNAL(messageReceived(QByteArray)));

         manager1.sendMessage( msg );
         int splitPoint = dev1.buffer().size()/2;

         sendDataToDev2( dev1.buffer().left( splitPoint ) );
         QCOMPARE(dev2ReadyReadSpy.count(), 1);
         QCOMPARE(spy.count() , 0);

         sendDataToDev2( dev1.buffer().mid( splitPoint ) );
         QCOMPARE(dev2ReadyReadSpy.count(), 2);
         // Check that message was splited correctly
         QCOMPARE(dev1.buffer() , dev2.buffer());
         QCOMPARE(spy.count() , 1);
         QCOMPARE(spy.first().at(0).toByteArray() , msg);
      };
   private:
      QBuffer dev1,dev2;
      qrs::DeviceManager manager1,manager2;

      void sendDataToDev2(const QByteArray& data) {
         qint64 pos = dev2.pos();
         dev2.write( data );
         dev2.seek(pos);
         QTest::qWait(1); // Return to qt event loop to allow it process asincronious signals
      }
};

QTEST_MAIN(DeviceManagerTests)
#include "devicemanagertests.moc"