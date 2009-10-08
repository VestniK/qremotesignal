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

#include <QtTest>
#include <QtDebug>

const QString TEST_SERVICE_NAME = "test";
const QString TEST_METHOD_NAME = "do";

/**
 * @brief qrs::Message comparision
 *
 * This operator defined to simplify tests there is no necesity to move it to the
 * class qrs::Message itself.
 */
bool operator== (const qrs::Message& msg1, const qrs::Message& msg2);

void printParam(const QVariant& param, int indent, QTextStream& out);
void printMapParam(const QVariantMap& param, int indent, QTextStream& out);
void printListParam(const QVariantList& param, int indent, QTextStream& out);
namespace QTest {
   /**
    * @brief qrs::Message textual representation for debug printing
    */
   template<>
   char* toString (const qrs::Message& msg) {
      QString buf;
      buf.clear();
      QTextStream out(&buf, QIODevice::WriteOnly);
      out << endl << "Type:\t";
      switch ( msg.type() ) {
         case qrs::Message::RemoteCall :
            out << "qrs::Message::RemoteCall" << endl;
            break;
         case qrs::Message::Error :
            out << "qrs::Message::Error" << endl;
            break;
         default:
            out << "Unknown type (" << (int)msg.type() << ")" << endl;
      }
      out << "Error type:\t";
      switch ( msg.errorType() ) {
         case qrs::Message::Ok :
            out << "qrs::Message::Ok" << endl;
            break;
         case qrs::Message::IncorrectMethod :
            out << "qrs::Message::IncorrectMethod" << endl;
            break;
         case qrs::Message::UnknownErrorCode :
            out << "qrs::Message::UnknownErrorCode" << endl;
            break;
         case qrs::Message::ProtocolError :
            out << "qrs::Message::ProtocolError" << endl;
            break;
         case qrs::Message::UnknownService :
            out << "qrs::Message::UnknownService" << endl;
            break;
         case qrs::Message::UnknownMsgType :
            out << "qrs::Message::UnknownMsgType" << endl;
            break;
         default:
            out << "Unknown error type (" << (int)msg.errorType() << ")" << endl;
      }
      out << "Error string:\t\"" << msg.error() << "\"" << endl;
      out << "Service:\t\"" << msg.service() << "\"" << endl;
      out << "Method:\t\t\"" << msg.method() << "\"" << endl;

      out << endl << "Arguments:\t";
      printMapParam(msg.params(), 0 , out);
      return qstrdup( buf.toLocal8Bit().constData() );
   }
}

void SerializersTestSuit::addDeserializationErrorTestCase(const QString& name, const QByteArray& msg) {
   mRawMessages.insert(name,msg);
}

void SerializersTestSuit::addOneArgRemoteCallTest(const QString& testName, const QVariant& arg) {
   qrs::Message *msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->params().insert("arg",arg);
   if ( mMessages.contains(testName) ) {
      qWarning() << "Trying to create several tests with the same name: " << testName;
      qWarning() << "Previous test is removed from tests list";
   }
   mMessages.insert(testName,msg);
}

/**
 * @brief filling test messages list
 */
void SerializersTestSuit::initTestCase() {
   qrs::Message *msg;

   // --- Errors
   // Unknown error
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->setErrorType(qrs::Message::UnknownErrorCode);
   msg->setError("error description");
   mMessages.insert("unknown error",msg);

   // Protocol error
   msg = new qrs::Message;
   msg->setErrorType(qrs::Message::ProtocolError);
   msg->setError("error description");
   mMessages.insert("protocol error",msg);

   // Unknown message type
   msg = new qrs::Message;
   msg->setErrorType(qrs::Message::UnknownMsgType);
   msg->setError("error description");
   mMessages.insert("unknown type",msg);

   // Unknown service
   msg = new qrs::Message;
   msg->setMethod(TEST_METHOD_NAME);
   msg->setErrorType(qrs::Message::UnknownService);
   msg->setError("error description");
   mMessages.insert("unknown service",msg);

   // Incorrect method
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->setErrorType(qrs::Message::IncorrectMethod);
   msg->setError("error description");
   mMessages.insert("incorrect method",msg);

   // --- Remote calls
   // No args
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   mMessages.insert("no args",msg);

   // unsigned char
   addOneArgRemoteCallTest("unsigned char",qrs::createArg( (unsigned char)45 ));
   // min unsigned char
   addOneArgRemoteCallTest("min unsigned char",qrs::createArg( std::numeric_limits<unsigned char>::min() ));
   // max unsigned char
   addOneArgRemoteCallTest("max unsigned char",qrs::createArg( std::numeric_limits<unsigned char>::max() ));
   // signed char
   addOneArgRemoteCallTest("signed char",qrs::createArg( (signed char)-76 ));
   // min signed char
   addOneArgRemoteCallTest("min signed shar",qrs::createArg( std::numeric_limits<signed char>::min() ));
   // max signed char
   addOneArgRemoteCallTest("max signed char",qrs::createArg( std::numeric_limits<signed char>::max() ));
   // short
   addOneArgRemoteCallTest("short",qrs::createArg( short(-123) ));
   // min short
   addOneArgRemoteCallTest("min short",qrs::createArg( std::numeric_limits<short>::min() ));
   // max short
   addOneArgRemoteCallTest("max short",qrs::createArg( std::numeric_limits<short>::max() ));
   // unsigned short
   addOneArgRemoteCallTest("unsigned short",qrs::createArg( (unsigned short)50 ));
   // min ushort
   addOneArgRemoteCallTest("min unsigned short",qrs::createArg( std::numeric_limits<unsigned short>::min() ));
   // max ushort
   addOneArgRemoteCallTest("max unsigned short",qrs::createArg( std::numeric_limits<unsigned short>::max() ));
   // int
   addOneArgRemoteCallTest("int",qrs::createArg( int(123) ));
   // min int
   addOneArgRemoteCallTest("min int",qrs::createArg( std::numeric_limits<int>::min() ));
   // max int
   addOneArgRemoteCallTest("max int",qrs::createArg( std::numeric_limits<int>::max() ));
   // unsigned
   addOneArgRemoteCallTest("unsigned",qrs::createArg( (unsigned)45000 ));
   // min unsigned
   addOneArgRemoteCallTest("min unsigned",qrs::createArg( std::numeric_limits<unsigned>::min() ));
   // max unsigned
   addOneArgRemoteCallTest("max unsigned",qrs::createArg( std::numeric_limits<unsigned>::max() ));
   // min long
   addOneArgRemoteCallTest("min long",qrs::createArg( std::numeric_limits<long>::min() ));
   // max long
   addOneArgRemoteCallTest("max long",qrs::createArg( std::numeric_limits<long>::max() ));
   // min unsigned long
   addOneArgRemoteCallTest("min unsigned long",qrs::createArg( std::numeric_limits<unsigned long>::min() ));
   // max unsigned long
   addOneArgRemoteCallTest("max unsigned long",qrs::createArg( std::numeric_limits<unsigned long>::max() ));
   // min long long
   addOneArgRemoteCallTest("min long long",qrs::createArg( std::numeric_limits<long long>::min() ));
   // max long long
   addOneArgRemoteCallTest("max long long",qrs::createArg( std::numeric_limits<long long>::max() ));
   // min unsigned long long
   addOneArgRemoteCallTest("min unsigned long long",qrs::createArg( std::numeric_limits<unsigned long long>::min() ));
   // max unsigned long
   addOneArgRemoteCallTest("max unsigned long long",qrs::createArg( std::numeric_limits<unsigned long long>::max() ));
   // bool true
   addOneArgRemoteCallTest("bool true",qrs::createArg(true));
   // bool false
   addOneArgRemoteCallTest("bool false",qrs::createArg(false));
   // QString
   addOneArgRemoteCallTest("QString",qrs::createArg( QString("string") ));
   // empty QString
   addOneArgRemoteCallTest("empty QString",qrs::createArg( QString("") ));
   // QList
   addOneArgRemoteCallTest("QList",qrs::createArg( QList<QString>() << "2" << "4" << "6" ));
   // empty QList
   addOneArgRemoteCallTest("empty QList",qrs::createArg( QList<QString>() ));
   // QMap
   QMap<QString,int> intMap;
   intMap["one"]=1;
   intMap["two"]=2;
   intMap["three"]=3;
   addOneArgRemoteCallTest("QMap",qrs::createArg( intMap ));
   // empty QMap
   addOneArgRemoteCallTest("empty QMap",qrs::createArg( QMap<QString,unsigned>() ));


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
      qrs::getArgValue(res->params()["arg"] , res_arg);
      QCOMPARE(res_arg , arg);
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
      qrs::getArgValue(res->params()["arg"] , res_arg);
      QCOMPARE(res_arg , arg);
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
   } catch ( const std::exception& e ) {
      qWarning("Caught exception of incorrect type");
      QFAIL( e.what() );
   } catch (...) {
      QFAIL("Caught exception of unknown type");
   }
}

// Additional stuff
bool qrsCompareParams(const QVariant param1 , const QVariant& param2);
bool qrsCompareMapParams(const QVariantMap& params1 , const QVariantMap& params2);
bool qrsCompareListParams(const QVariantList& list1 , const QVariantList& list2);

bool operator== (const qrs::Message& msg1, const qrs::Message& msg2) {
   if ( msg1.type()      != msg2.type()      ) return false;
   if ( msg1.errorType() != msg2.errorType() ) return false;
   if ( msg1.error()     != msg2.error()     ) return false;
   if ( msg1.service()   != msg2.service()   ) return false;
   if ( msg1.method()    != msg2.method()    ) return false;

   return qrsCompareMapParams(msg1.params() , msg2.params());
}

bool qrsCompareParams(const QVariant param1 , const QVariant& param2) {
   if ( param1.type() == QVariant::Map ) {
      if ( param2.type() != QVariant::Map ) return false;
      return qrsCompareMapParams(param1.toMap() , param2.toMap());
   } else if ( param1.type() == QVariant::List ) {
      if ( param2.type() != QVariant::List ) return false;
      return qrsCompareListParams(param1.toList(),param2.toList());
   } else if ( param1.canConvert<QString>() ) {
      if ( ! param2.canConvert<QString>() ) return false;
      return ( param1.toString() == param2.toString() );
   }
   qWarning("Can't compare params (corresponding QVariant can't be converted to string). Assuming them equal");
   return true;
}

bool qrsCompareMapParams(const QVariantMap& params1 , const QVariantMap& params2) {
   QVariantMap::const_iterator it = params1.begin();
   while ( it != params1.end() ) {
      if ( !params2.contains(it.key()) ) return false;
      if ( !qrsCompareParams(it.value() , params2.value(it.key())) ) return false;
      it++;
   }
   return true;
}

bool qrsCompareListParams(const QVariantList& list1 , const QVariantList& list2) {
   if ( list1.size() != list2.size() ) return false;
   for ( int i = 0; i < list1.size(); i++ ) {
      if ( !qrsCompareParams(list1[i],list2[i]) ) return false;
   }
   return true;
}

void printParam(const QVariant& param, int indent, QTextStream& out) {
   if ( param.type() == QVariant::Map ) {
      out << "Map ";
      printMapParam(param.toMap(), indent+1, out);
   } else if ( param.type() == QVariant::List ) {
      out << "List ";
      printListParam(param.toList(), indent+1, out);
   } else if ( param.canConvert<QString>() ) {
      out << "\"" << param.toString() << "\"" << endl;
   } else {
      out << "(Can't convert arg value to string)" << endl;
   }
}

void printMapParam(const QVariantMap& param, int indent, QTextStream& out) {
   QVariantMap::const_iterator it = param.begin();
   out << "{" << endl;
   while ( it != param.end() ) {
      for ( int i = 0; i < indent; i++ ) {
         out << " ";
      }
      out << "[" << it.key() << "]" << " = ";
      printParam(it.value(),indent+1,out);
      it++;
   }
   for ( int i = 0; i < indent; i++ ) {
      out << " ";
   }
   out << "}" << endl;
}

void printListParam(const QVariantList& param, int indent, QTextStream& out) {
   out << "{" << endl;
   for (int i = 0; i < param.size(); i++) {
      for ( int j = 0; j < indent; j++ ) {
         out << " ";
      }
      out << i << ": ";
      printParam(param[i], indent+1, out);
   }
   for ( int i = 0; i < indent; i++ ) {
      out << " ";
   }
   out << "}" << endl;
}
