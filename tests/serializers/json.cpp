/**
 * @file json.cpp
 * @brief Entry point for JsonSerializer tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#include <QtTest>

#include "serializerstestsuit.h"
#include "jsonserializer.h"

int main(int argc, char** argv) {
   qrs::JsonSerializer json;
   SerializersTestSuit testsuit(&json);
   return QTest::qExec(&testsuit,argc,argv);
}
