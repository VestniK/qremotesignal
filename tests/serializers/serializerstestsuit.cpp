/**
 * @file serializerstestsuit.cpp
 * @brief Serializers test suit
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#include "serializerstestsuit.h"

#include <exception>
#include <limits>

#include <QtCore/QtDebug>

#include "messagetesttools.h"

typedef QMap<QString,int> QIntMap;

Q_DECLARE_METATYPE(QList<int>);
Q_DECLARE_METATYPE(QIntMap);
Q_DECLARE_METATYPE(signed char);

const QString TEST_SERVICE_NAME = "test";
const QString TEST_METHOD_NAME = "do";

void SerializersTestSuit::addDeserializationErrorTestCase(const QString& name, const QByteArray& msg) {
   mRawMessages.insert(name,msg);
}

/**
 * @brief filling test messages list
 */
void SerializersTestSuit::initTestCase() {
   qRegisterMetaType< QList<int> >("QList<int>");
   qRegisterMetaType< QMap<QString,int> >("QMap<QString,int>");
   qRegisterMetaType<signed char>("signed char");

   qrs::Message *msg;

   // --- Errors
   // Unknown error
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->setErrorType(qrs::Message::UnknownErrorCode);
   msg->setError("error description");
   msg->setType(qrs::Message::Error);
   mMessages.insert("unknown error",msg);

   // Protocol error
   msg = new qrs::Message;
   msg->setErrorType(qrs::Message::ProtocolError);
   msg->setError("error description");
   msg->setType(qrs::Message::Error);
   mMessages.insert("protocol error",msg);

   // Unknown message type
   msg = new qrs::Message;
   msg->setErrorType(qrs::Message::UnknownMsgType);
   msg->setError("error description");
   msg->setType(qrs::Message::Error);
   mMessages.insert("unknown type",msg);

   // Unknown service
   msg = new qrs::Message;
   msg->setMethod(TEST_METHOD_NAME);
   msg->setErrorType(qrs::Message::UnknownService);
   msg->setError("error description");
   msg->setType(qrs::Message::Error);
   mMessages.insert("unknown service",msg);

   // Incorrect method
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->setErrorType(qrs::Message::IncorrectMethod);
   msg->setError("error description");
   msg->setType(qrs::Message::Error);
   mMessages.insert("incorrect method",msg);

   // --- Remote calls
   // No args
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   mMessages.insert("no args",msg);

   // Two args
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->params().insert("str",qrs::createArg( QString("string") ));
   msg->params().insert("list",qrs::createArg( QList<int>() << 2 << 4 << 8 << 16 ));
   mMessages.insert("Two args",msg);
}
void SerializersTestSuit::cleanupTestCase(){
   QMap<QString,qrs::Message*>::iterator indx = mMessages.begin();
   while ( indx != mMessages.end() ) {
      delete indx.value();
      indx = mMessages.erase(indx);
   }
}

void SerializersTestSuit::testQCharSerialization_data() {
   QTest::addColumn<QChar>("arg");

   QTest::newRow("1") << QChar('1');
   QTest::newRow("null") << QChar('\0');
   QTest::newRow("latin") << QChar('l');
}
void SerializersTestSuit::testQCharSerialization() {
   QFETCH(QChar,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      QChar res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support QChar serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testCharSerialization_data() {
   QTest::addColumn<char>("arg");

   QTest::newRow("a") << 'a';
   QTest::newRow("0") << '0';
   QTest::newRow("null") << '\0';
   QTest::newRow("min") << std::numeric_limits<char>::min();
   QTest::newRow("max") << std::numeric_limits<char>::max();
}
void SerializersTestSuit::testCharSerialization() {
   QFETCH(char,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      char res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support char serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

// signed char
void SerializersTestSuit::testSignedCharSerialization_data() {
   QTest::addColumn<signed char>("arg");

   QTest::newRow("-1") << (signed char)-1;
   QTest::newRow("0") << (signed char)0;
   QTest::newRow("1") << (signed char)1;
   QTest::newRow("min") << std::numeric_limits<signed char>::min();
   QTest::newRow("max") << std::numeric_limits<signed char>::max();
}
void SerializersTestSuit::testSignedCharSerialization() {
   QFETCH(signed char,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      signed char res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support signed char serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testUnsignedCharSerialization_data() {
   QTest::addColumn<unsigned char>("arg");

   QTest::newRow("0") << (unsigned char)0;
   QTest::newRow("1") << (unsigned char)1;
   QTest::newRow("min") << std::numeric_limits<unsigned char>::min();
   QTest::newRow("max") << std::numeric_limits<unsigned char>::max();
}
void SerializersTestSuit::testUnsignedCharSerialization() {
   QFETCH(unsigned char,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      unsigned char res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support unsigned serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testShortSerialization_data() {
   QTest::addColumn<short>("arg");

   QTest::newRow("min") << std::numeric_limits<short>::min();
   QTest::newRow("-1") << (short)-1;
   QTest::newRow("0") << (short)0;
   QTest::newRow("1") << (short)1;
   QTest::newRow("max") << std::numeric_limits<short>::max();
}
void SerializersTestSuit::testShortSerialization() {
   QFETCH(short,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      short res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support short serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testUShortSerialization_data() {
   QTest::addColumn<unsigned short>("arg");

   QTest::newRow("min") << std::numeric_limits<unsigned short>::min();
   QTest::newRow("0") << (unsigned short)0;
   QTest::newRow("1") << (unsigned short)1;
   QTest::newRow("max") << std::numeric_limits<unsigned short>::max();
}
void SerializersTestSuit::testUShortSerialization() {
   QFETCH(unsigned short,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      unsigned short res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support unsigned short serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testIntSerialization_data() {
   QTest::addColumn<int>("arg");

   QTest::newRow("1") << 1;
   QTest::newRow("-100") << -100;
   QTest::newRow("0") << 0;
   QTest::newRow("32000") << 32000;
   QTest::newRow("min") << std::numeric_limits<int>::min();
   QTest::newRow("max") << std::numeric_limits<int>::max();
}
void SerializersTestSuit::testIntSerialization() {
   QFETCH(int,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      int res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      qWarning("This serializer doesn't support int serialization");
      QFAIL( e.what() );
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testUIntSerialization_data() {
   QTest::addColumn<unsigned>("arg");

   QTest::newRow("1") << 1u;
   QTest::newRow("0") << 0u;
   QTest::newRow("32000") << 32000u;
   QTest::newRow("min") << std::numeric_limits<unsigned>::min();
   QTest::newRow("max") << std::numeric_limits<unsigned>::max();
}
void SerializersTestSuit::testUIntSerialization() {
   QFETCH(unsigned,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      unsigned res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support unsigned int serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testLongSerialization_data() {
   QTest::addColumn<long>("arg");

   QTest::newRow("-1") << -1l;
   QTest::newRow("1") << 1l;
   QTest::newRow("0") << 0l;
   QTest::newRow("min") << std::numeric_limits<long>::min();
   QTest::newRow("max") << std::numeric_limits<long>::max();
}
void SerializersTestSuit::testLongSerialization() {
   QFETCH(long,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      long res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support long serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testULongSerialization_data() {
   QTest::addColumn<unsigned long>("arg");

   QTest::newRow("1") << 1ul;
   QTest::newRow("0") << 0ul;
   QTest::newRow("min") << std::numeric_limits<unsigned long>::min();
   QTest::newRow("max") << std::numeric_limits<unsigned long>::max();
}
void SerializersTestSuit::testULongSerialization() {
   QFETCH(unsigned long,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      unsigned long res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support unigned long serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testLongLongSerialization_data() {
   QTest::addColumn<long long>("arg");

   QTest::newRow("-1") << -1ll;
   QTest::newRow("1") << 1ll;
   QTest::newRow("0") << 0ll;
   QTest::newRow("min") << std::numeric_limits<long long>::min();
   QTest::newRow("max") << std::numeric_limits<long long>::max();
}
void SerializersTestSuit::testLongLongSerialization() {
   QFETCH(long long,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      long long res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support long long serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testULongLongSerialization_data() {
   QTest::addColumn<unsigned long long>("arg");

   QTest::newRow("1") << 1ull;
   QTest::newRow("0") << 0ull;
   QTest::newRow("min") << std::numeric_limits<unsigned long long>::min();
   QTest::newRow("max") << std::numeric_limits<unsigned long long>::max();
}
void SerializersTestSuit::testULongLongSerialization() {
   QFETCH(unsigned long long,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      unsigned long long res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support unsigned long long serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testBoolSerialization_data() {
   QTest::addColumn<bool>("arg");

   QTest::newRow("true") << true;
   QTest::newRow("false") << false;
}
void SerializersTestSuit::testBoolSerialization() {
   QFETCH(bool,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      bool res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support bool serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testQStringSerialization_data() {
   QTest::addColumn<QString>("arg");

   QTest::newRow("word") << "word";
   QTest::newRow("line") << "Some line";
   QTest::newRow("two lines") << "Multiline string\nthere are 2 lines";
   QTest::newRow("empty") << QString();
}
void SerializersTestSuit::testQStringSerialization() {
   QFETCH(QString,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      QString res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      qWarning("This serializer doesn't support QString serialization");
      QFAIL( e.what() );
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testQListSerialization_data() {
   QTest::addColumn< QList<int> >("arg");

   QTest::newRow("simple") << ( QList<int>() << 1 << 2 << 3 << -4096 );
   QTest::newRow("empty") << QList<int>();
}
void SerializersTestSuit::testQListSerialization() {
   QFETCH(QList<int>,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      QList<int> res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support QList serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testQMapSerialization_data() {
   QTest::addColumn< QIntMap >("arg");

   QIntMap map;
   map["one"] = 1;
   map["two"] = 2;
   map["three"] = 3;
   QTest::newRow("simple") << map;
   QTest::newRow("empty") << QIntMap();
}
void SerializersTestSuit::testQMapSerialization() {
   QFETCH(QIntMap,arg);
   qrs::Message src;
   src.setService(TEST_SERVICE_NAME);
   src.setMethod(TEST_METHOD_NAME);
   src.params().insert("arg",qrs::createArg(arg));

   try {
      QByteArray raw = mSerializer->serialize( src );
      qrs::MessageAP res = mSerializer->deserialize(raw);

      QCOMPARE(*res , src);
      QIntMap res_arg;
      QVERIFY( qrs::getArgValue(res->params()["arg"] , res_arg) );
      QCOMPARE(res_arg , arg);
   } catch(const qrs::UnsupportedTypeException& e) {
      QSKIP("This serializer doesn't support QMap serialization",SkipAll);
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testSerialization_data() {
   QTest::addColumn<QString>("key");

   QMap<QString,qrs::Message*>::iterator indx = mMessages.begin();
   while ( indx != mMessages.end() ) {
      QTest::newRow( indx.key().toLocal8Bit().constData() ) << indx.key();
      indx++;
   }
}
void SerializersTestSuit::testSerialization() {
   QFETCH(QString,key);

   try {
      QByteArray raw = mSerializer->serialize( *mMessages.value(key) );
      qrs::MessageAP msg = mSerializer->deserialize(raw);

      QCOMPARE(*msg , *mMessages.value(key));
   } catch(const qrs::UnsupportedTypeException& e) {
      qWarning("Unsupported type");
      QFAIL( e.what() );
   } catch(const qrs::MessageParsingException& e) {
      qWarning("Can't parse message created by myself");
      QFAIL( e.what() );
   } catch(const std::exception& e) {
      qWarning("std::exception");
      QFAIL( e.what() );
   } catch( ... ) {
      QFAIL("Exception of unknown type");
   }
}

void SerializersTestSuit::testDeserializationError_data() {
   QTest::addColumn<QByteArray>("rawMsg");

   QMap<QString,QByteArray>::iterator indx = mRawMessages.begin();
   while ( indx != mRawMessages.end() ) {
      QTest::newRow( indx.key().toLocal8Bit().constData() ) << indx.value();
      indx++;
   }
   if ( !mRawMessages.contains("empty") ) {
      QTest::newRow("empty") << QByteArray();
   }
}
void SerializersTestSuit::testDeserializationError() {
   QFETCH(QByteArray,rawMsg);

   try {
      qrs::JsonSerializer serializer;
      serializer.deserialize(rawMsg);
      QFAIL("Incorrect message was parsed. Exception wasn't thrown");
   } catch (const qrs::MessageParsingException& e) {
      // All ok the message given should cause this exception
   } catch ( const std::exception& e ) {
      qWarning("Caught exception of incorrect type");
      QFAIL( e.what() );
   } catch (...) {
      QFAIL("Caught exception of unknown type");
   }
}
