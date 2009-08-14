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
#include <QtSoapMessage>

#include "absservice.h"

class ComunicationManager : public QObject {
   Q_OBJECT
   public:
      ComunicationManager(QObject *parent = 0);
      virtual ~ComunicationManager() {};

      void registerService(AbsService* service);
      void sendMessage(const QtSoapMessage& msg);
   public slots:
      void recieve(const QString& msg);
   signals:
      void send(QString msg);
   private:
      QMap<QString,AbsService*> services;
};

#endif
