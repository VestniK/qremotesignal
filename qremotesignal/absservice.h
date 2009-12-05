/**
 * @file absservice.h
 * @brief AbsService class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _AbsService_H
#define _AbsService_H

#include <QtCore>

#include "qrsexport.h"
#include "baseexception.h"
#include "message.h"

namespace qrs {

   class ServicesManager;

   /**
    * @brief Exception to be thrown on attempt to call unknown method
    *
    * @internal This exception is thrown inside service or client class
    * implementation generated from XML interface description by qrsc utility.
    * You don't have to catch it manually since it's caught by ServicesManager.
    *
    * @sa BaseException
    */
   class QRS_EXPORT IncorrectMethodException: public BaseException {
      public:
         IncorrectMethodException(const QString& msg):BaseException(msg) {};
   };

   /**
    * @brief Abstract interface for a service and client classes
    *
    * @internal
    * All classes generated from XML interface description are derived from
    * this class. You don't need to create you own implementations mannualy.
    */
   class QRS_EXPORT AbsService : public QObject {
      public:
         AbsService(QObject *parent = 0): QObject(parent),mManager(0) {}
         virtual ~AbsService() {}

         /**
          * @brief Process message and emmit necessary signals.
          *
          * This message is called by ServicesManager if recieved message
          * require to call a method of this service or client.
          */
         virtual void processMessage(const Message& msg)
               throw(IncorrectMethodException) = 0;
         /**
          * @brief Unique service name.
          *
          * Each service have it's unique name which is used during reistration
          * in a ServicesManager instance and is sended in remote call request
          * message. Service and Client classes shares the same name.
          *
          * @return service or client name.
          */
         virtual const QString& name() const = 0;

         /**
          * Sets ServicesManager instance which is used to send outgoing
          * messages. This method is called automatically by the
          * ServicesManager::registerService method. Normally you shouldn't
          * call it manually. But if you want for some cases use different
          * managers for incoming and outgoing messages then feel free to
          * use this method.
          */
         void setManager(ServicesManager* val) {mManager = val;}
         /**
          * @return ServicesManager instance which is used for sending outgoing
          * messages
          */
         ServicesManager* manager() {return mManager;}
         /**
          * @return constan pointer to ServicesManager instance which is used
          * for sending outgoing messages
          */
         const ServicesManager* manager() const {return mManager;}

      private:
         ServicesManager *mManager;
   };

/**
 * @page services_concept Services conception
 *
 * Each signal or slot shared using QRemoteSignal library should belong to some
 * service. Service can have any number of signals and slots. Each service has
 * a name which should be unique.
 *
 * Service is a class derived from AbsService abstract class. You don't have to
 * create it manualy since it should be creaed by @b qrsc utility from XML
 * file with remote interface description. See @ref qrsc for more detailes.
 *
 * Each service class instance should be registered in ServicesManager class
 * instance and then you can connect its signal and slots to your application
 * classes signal and slots. @note You can't register several services with the
 * same name in one ServicesManager instance.
 *
 * When you calls a slot in a service class it generates Message with remote
 * call request and sends it using ServicesManager. And each time Services
 * manager recieves a message with request for remote call adressed to your
 * service service class emits the signal specified in the request.
 *
 * Normally you have two services classes one to be used in a server applicatin
 * and another one is for client applicatin. Both of them are generated from
 * the same XML file. Each signal in one of tose two classes have corresponding
 * slot in another one class. Both signal and slot have the same name, same
 * parameters types and order. Those classes names beggins with service name
 * (which is the same for both services) and ends with @b Service for one class
 * and @b Client for another.
 */

}

#endif
