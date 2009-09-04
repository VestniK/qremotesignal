/**
 * @file comunicationmanager.h
 * @brief ComunicationManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _ComunicationManager_H
#define _ComunicationManager_H

#include <QtCore>

#include "absservice.h"
#include "absremotecallserializer.h"
#include "remotecall.h"

namespace qrs {

   class ComunicationManager : public QObject {
      Q_OBJECT
      public:
         ComunicationManager(QObject *parent = 0);
         virtual ~ComunicationManager() {};

         void registerService(AbsService* service);
         void send(const RemoteCall& msg);

         void setSerializer(AbsRemoteCallSerializer* val) {mSerializer = val;};
      public slots:
         void recieve(const QByteArray& msg);
      signals:
         void send(QByteArray msg);
      private:
         QMap< QString,AbsService*> mServices;
         AbsRemoteCallSerializer *mSerializer;
   };

}

#endif
