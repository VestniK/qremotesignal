/**
 * @file jsonserializertests.cpp
 * @brief JsonSerializer tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Sep 2009
 */
#include <QtCore>
#include <QtTest>

#include "jsonserializer.h"

class JsonSerializerTests: public QObject {
   Q_OBJECT
   private slots:
      void exceptionsTest_data() {
         QTest::addColumn<QByteArray>("message");

         QTest::newRow("NotJson") << (QByteArray)"12345";
         QTest::newRow("EmptyMessage") << (QByteArray)"{}";
         QTest::newRow("NoType") << (QByteArray)"{\"service\":\"Example\",\"method\":\"voidMethod\"}";
         QTest::newRow("WrongType") << (QByteArray)"{\"Wrong\":{\"service\":\"Example\",\"method\":\"voidMethod\"}}";
      }
      void exceptionsTest() {
         QFETCH(QByteArray,message);

         try {
            qrs::JsonSerializer serializer;
            serializer.deserialize(message);
            QFAIL("Exception wasn't thrown");
         } catch (const qrs::MessageParsingException& e) {
         }
      }
};

#include "jsonserializertests.moc"

QTEST_MAIN(JsonSerializerTests);