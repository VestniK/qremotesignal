/**
 * @file customtypestests.cpp
 * @brief QRemoteSignal library custom types support tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 16 Sep 2009
 */
#include <QtCore>
#include <QtTest>

#include "QRemoteSignal"

#include "customstruct.h"

#include "customtypeservice.h"
#include "customtypeclient.h"

class CustomTypesTests: public QObject {
   Q_OBJECT
   public slots:
      void receive(const CustomStruct& val) {
         mLastReceived.mInt = val.mInt;
         mLastReceived.mString = val.mString;
      }
   private slots:
      /// Prepare test environment
      void initTestCase() {
         mServerManager = new qrs::ServicesManager(this);
         mClientManager = new qrs::ServicesManager(this);
         mSerializer = new qrs::JsonSerializer(this);
         mServerManager->setSerializer(mSerializer);
         mClientManager->setSerializer(mSerializer);
         connect(mServerManager,SIGNAL(send(QByteArray)),
                 mClientManager,SLOT(receive(const QByteArray&)));
         connect(mClientManager,SIGNAL(send(QByteArray)),
                 mServerManager,SLOT(receive(const QByteArray&)));
         mService = new qrs::CustomTypeService(mServerManager);
         mClient = new qrs::CustomTypeClient(mClientManager);

         qRegisterMetaType<CustomStruct>("CustomStruct");
      }
      /// Cleanup test environment
      void cleanupTestCase() {
      }

      void sendCustomStructTest_data() {
         QTest::addColumn<int>("mInt");
         QTest::addColumn<QString>("mString");

         QTest::newRow("1") << 1 << "one";
         QTest::newRow("2") << 2 << "two";
         QTest::newRow("3") << 1 << "three";
      }
      void sendCustomStructTest() {
         QSignalSpy spy( mService,SIGNAL(sendCustomStruct(CustomStruct)) );
         connect(mService,SIGNAL(sendCustomStruct(CustomStruct)),
                 this,SLOT(receive(const CustomStruct&)));
         QFETCH(int, mInt);
         QFETCH(QString, mString);

         CustomStruct sent;
         sent.mInt = mInt;
         sent.mString = mString;
         mClient->sendCustomStruct(sent);

         QCOMPARE( spy.count(), 1 );

         QCOMPARE(mLastReceived.mInt , sent.mInt);
         QCOMPARE(mLastReceived.mString , sent.mString);
      }

   private:
      qrs::ServicesManager *mServerManager,*mClientManager;
      qrs::CustomTypeService *mService;
      qrs::CustomTypeClient *mClient;
      qrs::JsonSerializer *mSerializer;

      CustomStruct mLastReceived;
};

#include "customtypestests.moc"

QTEST_MAIN(CustomTypesTests);
