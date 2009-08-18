/**
 * @file serializationexceptions.h
 * @brief Serialization exceptions interface
 *
 * @author VestniK sir.vestnik@gmail.com
 * @date 18 Aug 2009
 */
#ifndef _SerializationExceptions_H
#define _SerializationExceptions_H

#include "baseexception.h"

namespace qrs{

   /**
    * @brief Unsupported type exception
    *
    * Exception to be thrown by AbsRemoteCallSerializer::serealize if remote
    * call object contains data types not supported by underlying protocol or
    * current serializer realization.
    */
   class UnsupportedTypeException: public BaseException {
      public:
         UnsupportedTypeException(const QString& msg):BaseException(msg) {};
   };

   /**
    * @brief Error during message parsing exception
    *
    * Exception to be thrown by AbsRemoteCallSerializer::deserealize if
    * message given as parameter is not valid underlying protocol message.
    */
   class MessageParsingException: public BaseException {
      public:
         MessageParsingException(const QString& msg):BaseException(msg) {};
   };

   /**
    * @brief Error message recieved exception
    *
    * Exception to be thrown by AbsRemoteCallSerializer::deserealize if
    * is valid underlying protocol message but representing an error instead
    * of remote call.
    */
   class ErrorMessageException: public BaseException {
      public:
         ErrorMessageException(const QString& msg): BaseException(msg) {};
   };

}

#endif
