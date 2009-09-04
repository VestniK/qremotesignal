/**
 * @file comunicationmanager.cpp
 * @brief ComunicationManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "comunicationmanager.h"

using namespace qrs;

ComunicationManager::ComunicationManager(QObject *parent): QObject(parent) {
   mSerializer = 0;
}

void ComunicationManager::recieve(const QByteArray& msg) {
   RemoteCallAP message;
   try {
      message = mSerializer->deserialize(msg);
   } catch (const ErrorMessageException& e) {
      /// @todo Create error handler class and process recieved error
      return;
   } catch (const MessageParsingException& e) {
      /// @todo Send error message here.
      return;
   }
   QMap<QString,AbsService*>::iterator res = mServices.find(message->service());
   if ( res != mServices.end() ) {
      try {
         (*res)->processMessage(*message);
      } catch ( IncorrectMethodException& err ) {
         /// @todo Send error message here.
         return;
      }
   } else {
      /// @todo Send error message here.
      return;
   }
}

void ComunicationManager::registerService(AbsService* service) {
   mServices[service->name()] = service;
}

void ComunicationManager::send(const RemoteCall& msg) {
   emit send( mSerializer->serialize(msg) );
}
