/**
 * @file json.cpp
 * @brief Entry point for JsonSerializer tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#include <QtTest/QtTest>

#include "serializerstestsuit.h"
#include "qjsonserializer.h"

int main(int argc, char** argv) {
   SerializersTestSuit testsuit(qjsonSerializer);

   testsuit.addDeserializationErrorTestCase("NotJson",(QByteArray)"12345");
   testsuit.addDeserializationErrorTestCase("EmptyMessage",(QByteArray)"{}");
   testsuit.addDeserializationErrorTestCase("NoType", (QByteArray)"{\"service\":\"Example\",\"method\":\"voidMethod\"}");
   testsuit.addDeserializationErrorTestCase("WrongType", (QByteArray)"{\"Wrong\":{\"service\":\"Example\",\"method\":\"voidMethod\"}}");

   return QTest::qExec(&testsuit,argc,argv);
}
