/**
 * @file absmessageserializer.h
 * @brief AbsMessageSerializer class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 15 Aug 2009
 */
#ifndef _AbsMessageSerializer_H
#define _AbsMessageSerializer_H

#include <QtCore>

#include "qrsexport.h"
#include "message.h"
#include "serializationexceptions.h"

namespace qrs {

   /**
    * @brief Abstrac tinterface for all remote call serializers.
    *
    * Serializer must provide two functions: serialize and deserialize. First
    * one converts instance of class qrs::Message (internal library message
    * representation) to raw underlying protocol message. The second one builds
    * instance of qrs::Message from raw protocol message. Instance created by the
    * deserialize function from raw messagege returned by the serialize function
    * should be equal to the initial instance.
    *
    * Current version of library comes with only one serializer JsonSerializer
    * but you can simply write your own serializer just implementing this two
    * functions.
    *
    * Once you've created your own serializer you can test it to compatibility
    * with this library using serializers test suit. You need to take 4 files
    * from the tests/serializers directory of the sources package of
    * QRemoteSignal library:
    * @li messagetesttools.h
    * @li messagetesttools.cpp
    * @li serializerstestsuit.h
    * @li serializerstestsuit.cpp
    *
    * Then you need to create instance of @b SerializersTestSuit class passing
    * to its constructor instance of you serializer class and run tests using
    * @b QTest::qExec function. You can also use @b addDeserializationErrorTestCase
    * method of the @b SerializersTestSuit class to test hat your serializer
    * throws MessageParsingException on attempt to deserialize some specific
    * raw messages.
    *
    * Here is example of main function for tests of the JsonSerializer class
    * which comes with this library:
    * @code
    * #include <QtTest>
    *
    * #include "serializerstestsuit.h"
    * #include "jsonserializer.h"
    *
    * int main(int argc, char** argv) {
    *    qrs::JsonSerializer json;
    *    SerializersTestSuit testsuit(&json);
    *
    *    testsuit.addDeserializationErrorTestCase("NotJson",(QByteArray)"12345");
    *    testsuit.addDeserializationErrorTestCase("EmptyMessage",(QByteArray)"{}");
    *    testsuit.addDeserializationErrorTestCase("NoType", (QByteArray)"{\"service\":\"Example\",\"method\":\"voidMethod\"}");
    *    testsuit.addDeserializationErrorTestCase("WrongType", (QByteArray)"{\"Wrong\":{\"service\":\"Example\",\"method\":\"voidMethod\"}}");
    *
    *    return QTest::qExec(&testsuit,argc,argv);
    * }
    * @endcode
    */
   class QRS_EXPORT AbsMessageSerializer: public QObject {
      public:
         AbsMessageSerializer(QObject* parent = 0): QObject(parent) {};
         virtual ~AbsMessageSerializer() {};

         /**
          * @brief Serealize Message
          *
          * @throw UnsupportedTypeException if remote call object contain data
          * which can't be converted to the underlying protocol message. For
          * example Message::params contain parameters of types not supported
          * by underlying protocol.
          *
          * @param msg Message class instance to be converted to a underlying
          * protocol message.
          *
          * @return raw underlying protocol message.
          *
          * @sa deserialize
          */
         virtual QByteArray serialize(const Message& msg)
               throw(UnsupportedTypeException) = 0;
         /**
          * @brief Deserealize Message
          *
          * @throw MessageParsingException in case of error during message
          * parsing
          *
          * @param msg underlying protocol raw message to be converted to a
          * Message class instance
          *
          * @return Message class instance
          *
          * @sa serialize
          */
         virtual MessageAP deserialize(const QByteArray& msg)
               throw(MessageParsingException) = 0;
   };

}

#endif
