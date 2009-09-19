/**
 * @file serializerstestsuit.cpp
 * @brief Serializers test suit
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#include "serializerstestsuit.h"

#include <exception>

const QString TEST_SERVICE_NAME = "test";
const QString TEST_METHOD_NAME = "do";

/**
 * @brief qrs::Message comparision
 *
 * This operator defined to simplify tests there is no necesity to move it to the
 * class qrs::Message itself.
 */
bool operator== (const qrs::Message& msg1, const qrs::Message msg2);

void SerializersTestSuit::addDeserializationErrorTestCase(const QString& name, const QByteArray& msg) {
   mRawMessages.insert(name,msg);
}

/**
 * @brief filling test messages list
 */
void SerializersTestSuit::initTestCase() {
   qrs::Message *msg;

   // int
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->params().insert("num",qrs::createArg( int(123) ));
   mMessages.insert("int",msg);

   // QString
   msg = new qrs::Message;
   msg->setService(TEST_SERVICE_NAME);
   msg->setMethod(TEST_METHOD_NAME);
   msg->params().insert("str",qrs::createArg( QString("string") ));
   mMessages.insert("QString",msg);
}
void SerializersTestSuit::cleanupTestCase(){
   QMap<QString,qrs::Message*>::iterator indx = mMessages.begin();
   while ( indx != mMessages.end() ) {
      delete indx.value();
      indx = mMessages.erase(indx);
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
}
void SerializersTestSuit::testDeserializationError() {
}

// Additional stuff
bool qrsCompareParams(const QVariant param1 , const QVariant& param2);
bool qrsCompareMapParams(const QVariantMap& params1 , const QVariantMap& params2);
bool qrsCompareListParams(const QVariantList& list1 , const QVariantList& list2);

bool operator== (const qrs::Message& msg1, const qrs::Message msg2) {
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
      if ( !qrsCompareMapParams(param1.toMap() , param2.toMap()) ) return false;
   } else if ( param1.type() == QVariant::List ) {
      if ( param2.type() != QVariant::List ) return false;
      if ( !qrsCompareListParams(param1.toList(),param2.toList()) ) return false;
   } else if ( param1.canConvert<QString>() ) {
      if ( param2.canConvert<QString>() ) return false;
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
