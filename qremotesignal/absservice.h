/**
 * @file absservice.h
 * @brief AbsService class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _AbsService_H
#define _AbsService_H

#include <QtCore/QObject>
#include <QtCore/QString>

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
          * in a ServicesManager instance and is sent in remote call request
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
          * messages.
          */
         ServicesManager* manager() {return mManager;}
         /**
          * @return constan pointer to ServicesManager instance which is used
          * for sending outgoing messages.
          */
         const ServicesManager* manager() const {return mManager;}

      private:
         ServicesManager *mManager;
   };

}

#endif
