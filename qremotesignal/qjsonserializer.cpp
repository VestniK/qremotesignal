/**
 * @file jsonserializer.cpp
 * @brief JsonSerializer implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Sep 2009
 */
#include "qjsonserializer.h"

// QJson
#include <qjson/parser.h>
#include <qjson/serializer.h>

// Json mesage types
const QString ERROR_TYPE = "Error";
const QString REMOTE_CALL_TYPE = "RemoteCall";
// General message keys
const QString SERVICE_KEY = "service";
const QString METHOD_KEY = "method";
// Error keys
const QString ERROR_DESCRIPTION_KEY = "description";
const QString ERROR_CODE_KEY = "errorCode";
// Remote call keys
const QString RC_PARAMS_KEY = "params";

using namespace qrs;

QByteArray JsonSerializer::serialize ( const Message& msg )
      throw(UnsupportedTypeException) {
   QJson::Serializer serializer;
   QVariantMap message;
   message.insert(SERVICE_KEY,msg.service());
   message.insert(METHOD_KEY,msg.method());

   QVariantMap jsonObject;
   if ( msg.type() == Message::RemoteCall ) {
      message.insert( RC_PARAMS_KEY,QVariant(msg.params()) );
      jsonObject.insert(REMOTE_CALL_TYPE,QVariant(message));
   } else if ( msg.type() == Message::Error ) {
      message.insert( ERROR_DESCRIPTION_KEY,msg.error() );
      message.insert( ERROR_CODE_KEY, (int)msg.errorType() );
      jsonObject.insert(ERROR_TYPE,QVariant(message));
   } else {
      /// @todo what to do if message type is incorrect?
   }
   return serializer.serialize( QVariant(jsonObject) );
}

MessageAP JsonSerializer::deserialize ( const QByteArray& msg )
      throw(MessageParsingException) {
   QJson::Parser parser;
   bool ok;
   // trying to parse incoming message
   QVariantMap result = parser.parse (msg, &ok).toMap();
   if ( !ok ) {
      QString desc = "JSON error. line %1: %2";
      desc = desc.arg(parser.errorLine()).arg(parser.errorString());
      MessageParsingException err(desc,Message::ProtocolError);
      throw( err );
   }
   if ( result.isEmpty() ) {
      QString desc = "Empty JSON message";
      MessageParsingException err(desc,Message::ProtocolError);
      throw( err );
   }
   // Checking message type
   QString messageType = result.keys().first();
   if ( messageType == ERROR_TYPE ) {
      QVariantMap msgBody = result[ERROR_TYPE].toMap();
      MessageAP err(new Message);
      err->setType(Message::Error);
      err->setError(msgBody.value(ERROR_DESCRIPTION_KEY).toString());
      err->setService(msgBody.value(SERVICE_KEY).toString());
      err->setMethod(msgBody.value(METHOD_KEY).toString());
      bool errCodeObtained = false;
      int errCode = msgBody.value(ERROR_CODE_KEY).toInt(&errCodeObtained);
      if ( errCodeObtained ) {
         switch ( errCode ) {
            case (int)Message::UnknownErrorCode:
               err->setErrorType(Message::UnknownErrorCode); break;
            case (int)Message::ProtocolError:
               err->setErrorType(Message::ProtocolError); break;
            case (int)Message::UnknownMsgType:
               err->setErrorType(Message::UnknownMsgType); break;
            case (int)Message::UnknownService:
               err->setErrorType(Message::UnknownService); break;
            case (int)Message::IncorrectMethod:
               err->setErrorType(Message::IncorrectMethod); break;
            default: err->setErrorType(Message::UnknownErrorCode);
         }
      } else {
         err->setErrorType(Message::UnknownErrorCode);
      }
      return err;
   } else if (messageType == REMOTE_CALL_TYPE) {
      // parsing remote call message
      QVariantMap rc = result[REMOTE_CALL_TYPE].toMap();
      MessageAP res(new Message);
      res->setService( rc.value(SERVICE_KEY).toString() );
      res->setMethod( rc.value(METHOD_KEY).toString() );
      res->setParams( rc.value(RC_PARAMS_KEY).toMap() );
      return res;
   } else {
      // Unknown message type
      QString desc = "Unknown message type \"%1\"";
      desc = desc.arg(messageType);
      MessageParsingException err(desc,Message::UnknownMsgType);
      throw( err );
   }
}
