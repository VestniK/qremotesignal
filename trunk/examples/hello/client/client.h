/**
 * @file client.h
 * @brief client interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#ifndef Client_H
#define Client_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QtGlobal>

#include "helloclient.h"

class QTcpSocket;

class Client: public QObject {
   Q_OBJECT
   public:
      explicit Client(QTcpSocket *socket, QObject *parent = 0);
      virtual ~Client() {};
      qrs::HelloClient *hello() {return mClient;}
   private slots:
      void onHello(const QString &greetings);
   private:
      qrs::HelloClient *mClient;
      QTcpSocket *mSocket;
};

#endif
