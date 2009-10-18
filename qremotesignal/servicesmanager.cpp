/**
 * @file servicesmanager.cpp
 * @brief ServicesManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "servicesmanager.h"

using namespace qrs;

ServicesManager::ServicesManager(QObject *parent): QObject(parent) {
   mSerializer = 0;
}

void ServicesManager::receive(const QByteArray& msg) {
   MessageAP message;
   try {
      message = mSerializer->deserialize(msg);
   } catch (const MessageParsingException& e) {
      Message err;
      err.setErrorType(e.mErrorType);
      err.setError( e.reason() );
      emit mSerializer->serialize(err);
      return;
   }
   if ( message->type() == Message::Error ) {
      /// @todo Create error handler class and process received error
      emit error();
      return;
   }
   QMap<QString,AbsService*>::iterator res = mServices.find(message->service());
   if ( res != mServices.end() ) {
      try {
         (*res)->processMessage(*message);
      } catch ( IncorrectMethodException& e ) {
         Message err;
         err.setErrorType(Message::IncorrectMethod);
         err.setError(e.reason());
         err.setService(message->service());
         err.setMethod(message->method());
         emit send( mSerializer->serialize(err) );
         return;
      }
   } else {
      Message err;
      err.setErrorType(Message::UnknownService);
      err.setError(QString("Unknown service: \"%1\"").arg(message->service()));
      err.setService(message->service());
      emit send( mSerializer->serialize(err) );
      return;
   }
}

void ServicesManager::registerService(AbsService* service) {
   mServices[service->name()] = service;
}

void ServicesManager::send(const Message& msg) {
   emit send( mSerializer->serialize(msg) );
}

/**
 * This member function provided for convenience.
 *
 * Automatically creates device manager which uses given device to send and
 * receive messages.
 *
 * @sa DeviceManager
 */
void ServicesManager::setDevice(QIODevice* dev) {
   if ( !mDevManager ) {
      mDevManager = QSharedPointer<DeviceManager>( new DeviceManager() );
      connect(mDevManager.data(),SIGNAL(received(QByteArray)),
              this,SLOT(receive(const QByteArray&)));
      connect(this,SIGNAL(send(QByteArray)),
              mDevManager.data(),SLOT(send(const QByteArray&)));
   }
   mDevManager->setDevice(dev);
}
