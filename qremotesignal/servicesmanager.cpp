/**
 * @file servicesmanager.cpp
 * @brief ServicesManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "servicesmanager.h"

using namespace qrs;

/**
 * Constructs new ServicesManager object. Serializer is not set
 */
ServicesManager::ServicesManager(QObject *parent): QObject(parent) {
   mSerializer = 0;
}

/**
 * @brief Process received raw message
 *
 * This slot can be connected to some signal of class produces raw messages. It
 * process received message and calls corresponding service message processor.
 *
 * If message require to call a method from a service which is not registered
 * in this ServicesManager it sends error message by emiting send(QByteArray)
 * signal. Error message will be send a service which method is called can't
 * process the message received (no such method, wrong arguments or arguments
 * types).
 *
 * This slot do nothing if serializer to serialize/deserialize raw messages is
 * not set.
 *
 * @sa send(QByteArray)
 * @sa AbsMessageSerializer
 *
 * @param msg received raw message
 */
void ServicesManager::receive(const QByteArray& msg) {
   if ( !mSerializer ) {
      return;
   }
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

/**
 * This function registers new serilizer in this ServicesManager. If service
 * with the same name have been already registerd it replace old service object
 * with the new one.
 *
 * Service name is determined with AbsService::name function.
 *
 * @sa AbsService
 *
 * @param service service object to be registered.
 */
void ServicesManager::registerService(AbsService* service) {
   mServices[service->name()] = service;
}

/**
 * @internal
 *
 * This function provided to be used by client classes generated from service
 * interface description. You should not use this function manually. It can be
 * renamed or removed in future versions.
 */
void ServicesManager::send(const Message& msg) {
   emit send( mSerializer->serialize(msg) );
}

/**
 * This member function provided for convenience.
 *
 * Automatically creates device manager which uses given device to send and
 * receive messages. Several devices may be added by this function. All of
 * them will be used to send/receive messages. If QIODevice object pointed by
 * the dev pointer is deleted corresponding DeviceManager will be removed
 * automatically.
 *
 * @param dev device to be used for sending/receiving messages
 * @sa DeviceManager
 */
void ServicesManager::addDevice(QIODevice* dev) {
   foreach (const QSharedPointer<DeviceManager> dm, mDevManagers) {
      if ( dm->device() == dev ) {
         return;
      }
   }
   QSharedPointer<DeviceManager> dm( new DeviceManager() );
   connect(dm.data(),SIGNAL(received(QByteArray)),
           this,SLOT(receive(const QByteArray&)));
   connect(this,SIGNAL(send(QByteArray)),
           dm.data(),SLOT(send(const QByteArray&)));
   dm->setDevice(dev);
   mDevManagers.append(dm);
   connect(dev,SIGNAL(destroyed( QObject* )),
           this,SLOT(onDeviceDeleted(QObject*)));
}

/**
 * This slot handles resources cleanup if one of the devices used by this
 * services manager to read write messages is deleted.
 */
void ServicesManager::onDeviceDeleted(QObject* dev) {
   QList< QSharedPointer<DeviceManager> >::iterator it;
   for ( it = mDevManagers.begin(); it != mDevManagers.end(); it++ ) {
      if ( (*it)->device() == dev ) {
         mDevManagers.erase(it);
         return;
      }
   }
}
