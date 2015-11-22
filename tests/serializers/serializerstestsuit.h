/**
 * @file serializerstestsuit.h
 * @brief Serializers test suit
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#ifndef _SerializersTestSuit_H
#define _SerializersTestSuit_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QByteArray>
#include <QtTest/QtTest>

#include "QRemoteSignal"
#include "templateconverters.h"

class SerializersTestSuit:public QObject{
   Q_OBJECT
   public:
      explicit SerializersTestSuit(qrs::AbsMessageSerializer* serializer) {
         mSerializer = serializer;
      }

      void addDeserializationErrorTestCase(const QString& name, const QByteArray& msg);
   private slots:
      void initTestCase();
      void cleanupTestCase();

      void testSerialization_data();
      void testSerialization();

      void testQCharSerialization_data();
      void testQCharSerialization();

      void testCharSerialization_data();
      void testCharSerialization();

      void testSignedCharSerialization_data();
      void testSignedCharSerialization();

      void testUnsignedCharSerialization_data();
      void testUnsignedCharSerialization();

      void testShortSerialization_data();
      void testShortSerialization();

      void testUShortSerialization_data();
      void testUShortSerialization();

      void testIntSerialization_data();
      void testIntSerialization();

      void testUIntSerialization_data();
      void testUIntSerialization();

      void testLongSerialization_data();
      void testLongSerialization();

      void testULongSerialization_data();
      void testULongSerialization();

      void testLongLongSerialization_data();
      void testLongLongSerialization();

      void testULongLongSerialization_data();
      void testULongLongSerialization();

      void testBoolSerialization_data();
      void testBoolSerialization();

      void testQStringSerialization_data();
      void testQStringSerialization();

      void testQListSerialization_data();
      void testQListSerialization();

      void testQMapSerialization_data();
      void testQMapSerialization();

//       void testDeserializationError_data();
//       void testDeserializationError();
   private:
      Q_DISABLE_COPY(SerializersTestSuit);

      qrs::AbsMessageSerializer *mSerializer;
      QMap<QString,qrs::Message*> mMessages;
      QMap<QString,QByteArray> mRawMessages;
};

#endif
