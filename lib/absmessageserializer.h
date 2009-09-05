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

#include "message.h"
#include "serializationexceptions.h"

namespace qrs {

   /**
    * @brief Abstrac tinterface for all remote call serializers.
    *
    * Serializer must provide two functions: serialize and deserialize. Those
    * functions should be inverse for each other. So the following statement
    * should be true: msg == deserialize(serialize(msg))
    */
   class AbsMessageSerializer: public QObject {
      public:
         AbsMessageSerializer(QObject* parent = 0): QObject(parent) {};
         virtual ~AbsMessageSerializer() {};

         /**
          * @brief Serealize Message
          *
          * @throw UnsupportedTypeException if remote call object contain data
          * which can't be converted to the underlying protocol message
          *
          * @sa deserialize
          *
          * @param msg Message class instance to be converted to a string
          * @return string representation of a remote call (SOAP, XML-RPC,
          * JSON ...)
          */
         virtual QByteArray serialize(const Message& msg)
               throw(UnsupportedTypeException) = 0;
         /**
          * @brief Serealize Message
          *
          * @throw MessageParsingException in case of error during message parsing
          * @throw ErrorMessageException if the message recieved is error message
          *
          * @sa serialize
          *
          * @param msg remote call string representation (SOAP, XML-RPC, JSON ...)
          * @return Message class instance
          */
         virtual MessageAP deserialize(const QByteArray& msg)
               throw(MessageParsingException) = 0;
   };

}

#endif
