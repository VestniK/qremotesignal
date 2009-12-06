/**
 * @file serializationexceptions.h
 * @brief Serialization exceptions interface
 *
 * @author VestniK sir.vestnik@gmail.com
 * @date 18 Aug 2009
 */
#ifndef _SerializationExceptions_H
#define _SerializationExceptions_H

#include "qrsexport.h"
#include "baseexception.h"
#include "message.h"

namespace qrs{

   /**
    * @brief Unsupported type exception
    *
    * Exception to be thrown by AbsMessageSerializer::serealize if remote
    * call object contains data types not supported by underlying protocol or
    * current serializer realization.
    *
    * Throw this exception in your custom serializer implementation.
    *
    * @sa BaseException
    */
   class QRS_EXPORT UnsupportedTypeException: public BaseException {
      public:
         UnsupportedTypeException(const QString& msg):BaseException(msg) {};
   };

   /**
    * @brief Error during message parsing exception
    *
    * Exception to be thrown by AbsMessageSerializer::deserealize if
    * message given as parameter is not valid underlying protocol message.
    *
    * Throw this exception in your custom serializer implementation.
    *
    * @sa BaseException
    */
   class QRS_EXPORT MessageParsingException: public BaseException {
      public:
         MessageParsingException(const QString& msg,Message::ErrorType val):BaseException(msg) {
            mErrorType = val;
         }

         Message::ErrorType mErrorType;
   };

}

#endif
