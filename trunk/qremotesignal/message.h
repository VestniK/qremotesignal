/**
 * @file message.h
 * @brief Message class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _Message_H
#define _Message_H

#include <memory>

#include <QtCore/QString>
#include <QtCore/QVariantMap>

#include "qrsexport.h"

namespace qrs {

   /**
    * @brief Message representation
    *
    * This class contains all necessary information about slot to be called in
    * remote application. It's used by the QRemoteSignal library as internall
    * remote call representation.
    *
    * It can also contain detailed description of error occured during remote
    * slot call.
    *
    * It's serealized to and deserialized from raw underlying protocol message
    * by one of the classes derived from AbsMessageSerializer class.
    *
    * @sa AbsMessageSerializer
    */
   class QRS_EXPORT Message {
      public:
         Message() {mType = RemoteCall; mErrorType = Ok;};
         ~Message() {};

         enum MsgType {RemoteCall,Error};
         enum ErrorType {
            /// if received error code is not described here or not received
            UnknownErrorCode = -1,
            /// If there is no error
            Ok = 0,
            /// Incorrect mesage from underlying protocol point of view
            ProtocolError = 1,
            /// Message type not specified
            UnknownMsgType = 2,
            /**
             * Service name not specified or this application doesn't share
             * such service
             */
            UnknownService = 3,
            /**
             * Method name not specified, no such methon in this service or
             * incorrect parameters given for this method.
             */
            IncorrectMethod = 4,
         };

         MsgType type() const {return mType;};
         void setType(MsgType val) {mType = val;};

         ErrorType errorType() const {return mErrorType;};
         void setErrorType(ErrorType val) {mType = Error; mErrorType = val;};

         /**
          * @brief Returns error description
          */
         const QString& error() const {return mError;};
         /**
          * @brief Set error description and change message type to Message::Error
          *
          * @param val human readable error description
          */
         void setError(const QString& val) {mError = val; mType = Error;};

         /**
          * @brief Set name of the destination service
          *
          * @param val destination service name
          *
          * @sa service
          */
         void setService ( const QString& val ) {mService = val;};
         /**
          * @brief Returns destination service name
          *
          * @return destination service name
          *
          * @sa service
          */
         const QString& service() const {return mService;};

         /**
          * @brief Sets method name
          * @param val new method name
          * @sa method
          */
         void setMethod ( const QString& val ) {mMethod = val;};
         /**
          * @brief Returns method name
          * @return current method name
          * @sa method
          */
         const QString& method() const {return mMethod;}

         const QVariantMap& params() const {return mParams;};
         QVariantMap& params() {return mParams;};
         void setParams(const QVariantMap& val) {mParams = val;};

      private:
         /**
          * @brief service name
          *
          * This property contains destination service name.
          *
          * Service is one of the base concepts of the QRemoteSignal library.
          * It's used to group several methods in a single unit. Each method
          * your application share should be a part of some service. There
          * is no limitations on the number of services in a single
          * application.
          *
          * @sa getService
          * @sa setService
          */
         QString mService;
         /**
          * @brief method name
          *
          * This property contains a name of the slot to be called
          *
          * @sa getMethod
          * @sa setMethod
          */
         QString mMethod;
         /**
          * @brief Map of method parameters.
          */
         QVariantMap mParams;

         MsgType mType;
         ErrorType mErrorType;

         /**
          * @brief Error description.
          *
          * Contains description of the received error message
          */
         QString mError;
   };

   typedef std::auto_ptr<Message> MessageAP;
}

#endif
