/**
 * @file comunicationmanager.cpp
 * @brief ComunicationManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "comunicationmanager.h"

#include <QtNetwork>
#include <QtSoapMessage>

#define ERROR_LINE_NAME "line"
#define ERROR_POS_NAME "pos"
#define UNKNOWN_URI "Services for '%1' are not supported"

using namespace qrs;

ComunicationManager::ComunicationManager(QObject *parent): QObject(parent) {
}

void ComunicationManager::recieve(const QString& msg) {
   QDomDocument xml;
   QString err;
   int line,pos;
   if ( ! xml.setContent(msg,true,&err,&line,&pos) ) {
      QtSoapMessage error;
      error.setFaultCode(QtSoapMessage::Client);
      error.setFaultString(err);
      QtSoapType *detail = new QtSoapSimpleType(QtSoapQName(ERROR_LINE_NAME,""),line);
      error.addFaultDetail(detail);
      detail = new QtSoapSimpleType(QtSoapQName(ERROR_POS_NAME,""),pos);
      error.addFaultDetail(detail);
      emit send(error.toXmlString());
      return;
   }
   QtSoapMessage message;
   if ( ! message.setContent(xml) ) {
      emit send(message.toXmlString());
      return;
   }
   if ( message.isFault() ) {
      /// @todo add fault messages support
      return;
   }
   QMap<QString,AbsService*>::iterator res = services.find( message.method().name().uri() );
   if ( res != services.end() ) {
      try {
         (*res)->processMessage( message.method() );
      } catch ( IncorrectMethodException& err ) {
         QtSoapMessage error;
         error.setMethod( message.method().name() );
         error.setFaultCode(QtSoapMessage::Client);
         error.setFaultString( err.getReason() );
         emit send(error.toXmlString());
         return;
      }
   } else {
      QtSoapMessage error;
      error.setFaultCode(QtSoapMessage::Client);
      err = UNKNOWN_URI;
      error.setFaultString( err.arg(message.method().name().uri()) );
      emit send(error.toXmlString());
      return;
   }
}

void ComunicationManager::registerService(AbsService* service) {
   services[service->getUri()] = service;
}

void ComunicationManager::sendMessage(const QtSoapMessage& msg) {
   emit send( msg.toXmlString() );
}
