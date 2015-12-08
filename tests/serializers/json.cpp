/**
 * @file json.cpp
 * @brief Entry point for JsonSerializer tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#include <QtTest/QtTest>

#include "serializerstestsuit.h"
#include "jsonserializer.h"

namespace
{

inline
QByteArray asciz2bytearray(const char *str) {
    return QByteArray::fromRawData(str, strlen(str));
}

}

int main(int argc, char** argv) {
   SerializersTestSuit testsuit(jsonSerializer);

   testsuit.addDeserializationErrorTestCase("NotJson", asciz2bytearray("12345"));
   testsuit.addDeserializationErrorTestCase("EmptyMessage",asciz2bytearray("{}"));
   testsuit.addDeserializationErrorTestCase("NoType", asciz2bytearray("{\"service\":\"Example\",\"method\":\"voidMethod\"}"));
   testsuit.addDeserializationErrorTestCase("WrongType", asciz2bytearray("{\"Wrong\":{\"service\":\"Example\",\"method\":\"voidMethod\"}}"));

   return QTest::qExec(&testsuit,argc,argv);
}
