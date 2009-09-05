/**
 * @file communicationmanager.h
 * @brief CommunicationManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _CommunicationManager_H
#define _CommunicationManager_H

#include <QtCore>

#include "absservice.h"
#include "absmessageserializer.h"
#include "message.h"

namespace qrs {

   class CommunicationManager : public QObject {
      Q_OBJECT
      public:
         CommunicationManager(QObject *parent = 0);
         virtual ~CommunicationManager() {};

         void registerService(AbsService* service);
         void send(const Message& msg);

         void setSerializer(AbsMessageSerializer* val) {mSerializer = val;};
      public slots:
         void recieve(const QByteArray& msg);
      signals:
         void send(QByteArray msg);
         /**
          * This signal is emmited if error message recieved.
          */
         void error();
      private:
         QMap< QString,AbsService*> mServices;
         AbsMessageSerializer *mSerializer;
   };

}

#endif
