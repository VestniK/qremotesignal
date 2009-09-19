/**
 * @file serializerstestsuit.h
 * @brief Serializers test suit
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Sep 2009
 */
#ifndef _SerializersTestSuit_H
#define _SerializersTestSuit_H

#include <QtCore>
#include <QtTest>

#include "QRemoteSignal"

class SerializersTestSuit:public QObject{
   Q_OBJECT
   public:
      SerializersTestSuit(qrs::AbsMessageSerializer* serializer) {
         mSerializer = serializer;
      }

      void addDeserializationErrorTestCase(const QString& name, const QByteArray& msg);
   private slots:
      void initTestCase();
      void cleanupTestCase();

      void testSerialization_data();
      void testSerialization();

      void testDeserializationError_data();
      void testDeserializationError();
   private:
      qrs::AbsMessageSerializer *mSerializer;
      QMap<QString,qrs::Message*> mMessages;
      QMap<QString,QByteArray> mRawMessages;
};

#endif
