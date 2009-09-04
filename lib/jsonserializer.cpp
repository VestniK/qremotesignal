/**
 * @file jsonserializer.cpp
 * @brief JsonSerializer implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Sep 2009
 */
#include "jsonserializer.h"

// QJson
#include <qjson/parser.h>
#include <qjson/serializer.h>

// Json mesage types
#define ERROR_TYPE "Error"
#define REMOTE_CALL_TYPE "RemoteCall"
// Error keys
#define ERROR_DESCRIPTION_KEY "description"
// Remote call keys
#define RC_SERVICE_KEY "service"
#define RC_METHOD_KEY "method"
#define RC_PARAMS_KEY "params"

using namespace qrs;

QByteArray JsonSerializer::serialize ( const RemoteCall& rc )
      throw(UnsupportedTypeException) {
   QJson::Serializer serializer;
   QVariantMap rcall;
   rcall.insert(RC_SERVICE_KEY,rc.service());
   rcall.insert(RC_METHOD_KEY,rc.method());
   rcall.insert( RC_PARAMS_KEY,QVariant(rc.params()) );
   QVariantMap jsonObject;
   jsonObject.insert(REMOTE_CALL_TYPE,QVariant(rcall));
   return serializer.serialize( QVariant(jsonObject) );
}

RemoteCallAP JsonSerializer::deserialize ( const QByteArray& msg )
      throw(MessageParsingException,ErrorMessageException) {
   QJson::Parser parser;
   bool ok;
   // trying to parse incoming message
   QVariantMap result = parser.parse (msg, &ok).toMap();
   if ( !ok ) {
      throw( MessageParsingException(tr("Json parsing error at line %1: %2").arg(parser.errorLine()).arg(parser.errorString())) );
   }
   // Checking message type
   QString messageType = result.keys().first();
   if ( messageType == ERROR_TYPE ) {
      QString errMsg = result[ERROR_TYPE].toMap().value(ERROR_DESCRIPTION_KEY).toString();
      if ( errMsg.isNull() ) {
         errMsg = tr("Unknown error message recieved");
      }
      throw( ErrorMessageException(errMsg) );
   }
   if ( messageType != REMOTE_CALL_TYPE ) {
      throw(MessageParsingException(tr("Message of unknown type")));
   }
   // parsing remote call message
   QVariantMap rc = result[REMOTE_CALL_TYPE].toMap();
   if ( ! rc.value(RC_SERVICE_KEY).isValid() ) {
      throw(MessageParsingException(tr("Service is not specified")));
   }
   if ( ! rc.value(RC_METHOD_KEY).isValid() ) {
      throw(MessageParsingException(tr("Method is not specified")));
   }
   if ( ! rc.value(RC_PARAMS_KEY).isValid() ) {
      throw(MessageParsingException(tr("Params are not specified")));
   }
   RemoteCallAP res(new RemoteCall);
   res->setService( rc[RC_SERVICE_KEY].toString() );
   res->setMethod( rc[RC_METHOD_KEY].toString() );
   res->setParams( rc[RC_PARAMS_KEY].toMap() );
   return res;
}
