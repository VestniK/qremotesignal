/**
 * @file soapserializer.cpp
 * @brief SoapSerializer class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Aug 2009
 */
#include "soapserializer.h"

#include <QtXml>

#include "qtsoap.h"

using namespace qrs;

QString SoapSerializer::serialize (const RemoteCall& rc)
      throw(UnsupportedTypeException) {
   QtSoapMessage msg;
   msg.setMethod(rc.getMethod(),rc.getService());
   QMap<QString,QVariant>::const_iterator param = paramsMap.constBegin();
   while ( param != paramsMap.constEnd() ) {
      QtSoapType* arg = createArg(param.key(), param.value());
      if ( arg == 0 ) {
         throw( UnsupportedTypeException(
                tr("Type %1 is not supported by SOAP serializer").arg(param.value().typeName()) ) );
      }
      msg.addMethodArgument( arg );
      param++;
   }
   return msg.toXmlString();
}

RemoteCall SoapSerializer::deserialize ( const QString& msg )
      throw(MessageParsingException,ErrorMessageException) {
   QDomDocument xml;
   QString err;
   int line,pos;
   if ( ! xml.setContent(msg,true,&err,&line,&pos) ) {
      throw( MessageParsingException(
             tr("Error (line %1, pos: %2): %3").arg(line).arg(pos).arg(err)
      ));
   }
   QtSoapMessage message;
   if ( ! message.setContent(xml) ) {
      throw( MessageParsingException(
             tr("Error: %1").arg(message.errorString())
      ));
   }
   if ( message.isFault() ) {
      throw( ErrorMessageException(message.faultString().toString()));
   }
   RemoteCall res;
   res.setService( message.method().name().uri() );
   res.setMethod( message.method().name().name() );
   /// @todo get all args and pack them to params map
}

QtSoapType* SoapSerializer::createArg(const QString& name, const QVariant value) {
   switch (value.type()) {
      case QVariant::Int: return new QtSoapSimpleType(name,value.toInt()); break;
      case QVariant::Bool: return new QtSoapSimpleType(name,value.toBool(),0); break;
      case QVariant::String: return new QtSoapSimpleType(name,value.toString()); break;
      default: break;
   }
   return 0;
}
