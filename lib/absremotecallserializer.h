/**
 * @file absremotecallserializer.h
 * @brief AbsRemoteCallSerializer class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 15 Aug 2009
 */
#ifndef _AbsRemoteCallSerializer_H
#define _AbsRemoteCallSerializer_H

#include <QtCore>

#include "remotecall.h"
#include "serializationexceptions.h"

namespace qrs {

   /**
    * @brief Abstrac tinterface for all remote call serializers.
    *
    * Serializer must provide two functions: serialize and deserialize. Those
    * functions should be inverse for each other. So the following statement
    * should be true: rc == deserialize(serialize(rc))
    */
   class AbsRemoteCallSerializer: public QObject {
      public:
         AbsRemoteCallSerializer(QObject* parent = 0): QObject(parent) {};
         virtual ~AbsRemoteCallSerializer() {};

         /**
          * @brief Serealize RemoteCall
          *
          * @throw UnsupportedTypeException if remote call object contain data
          * which can't be converted to the underlying protocol message
          *
          * @sa deserialize
          *
          * @param rc RemoteCall class instance to be converted to a string
          * @return string representation of a remote call (SOAP, XML-RPC,
          * JSON ...)
          */
         virtual QByteArray serialize(const RemoteCall& rc)
               throw(UnsupportedTypeException) = 0;
         /**
          * @brief Serealize RemoteCall
          *
          * @throw MessageParsingException in case of error during message parsing
          * @throw ErrorMessageException if the message recieved is error message
          *
          * @sa serialize
          *
          * @param msg remote call string representation (SOAP, XML-RPC, JSON ...)
          * @return RemoteCall class instance
          */
         virtual RemoteCallAP deserialize(const QByteArray& msg)
               throw(MessageParsingException,ErrorMessageException) = 0;
   };

}

#endif
