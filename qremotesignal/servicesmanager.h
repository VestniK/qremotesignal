/**
 * @file servicesmanager.h
 * @brief ServicesManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _ServicesManager_H
#define _ServicesManager_H

#include <QtCore>

#include "qrsexport.h"
#include "absservice.h"
#include "absmessageserializer.h"
#include "message.h"

namespace qrs {

   /**
    * @brief Class managing communications between services and clients.
    *
    * This class class is used by classes generated from XML remote interface
    * description to communicate with each other.
    */
   class QRS_EXPORT ServicesManager : public QObject {
      Q_OBJECT
      public:
         ServicesManager(QObject *parent = 0);
         virtual ~ServicesManager() {};

         void registerService(AbsService* service);
         void send(const Message& msg);

         void setSerializer(AbsMessageSerializer* val) {mSerializer = val;};
      public slots:
         void receive(const QByteArray& msg);
      signals:
         void send(QByteArray msg);
         /**
          * This signal is emmited if error message received.
          */
         void error();
      private:
         QMap< QString,AbsService*> mServices;
         AbsMessageSerializer *mSerializer;
   };

}

#endif
