/**
 * @file qdatastream.cpp
 * @brief Entry point for QDataStreamSerializer tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 27 Jan 2010
 */
#include <QtTest/QtTest>

#include "serializerstestsuit.h"
#include "qdatastreamserializer.h"

int main(int argc, char** argv) {
    SerializersTestSuit testsuit(qDataStreamSerializer);
    return QTest::qExec(&testsuit,argc,argv);
}
