/**
 * @file server.cpp
 * @brief Server implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#include "server.h"

#include <stdio.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QTextStream>
#include <QtCore/QTimer>

#include <QRemoteSignal>

#include "printservice.h"

#define CLEANUP_INTERVAL 1000 //ms

Server::Server (QObject *parent):QObject(parent) {
   mTcpSrv = new QTcpServer(this);
   connect(mTcpSrv,SIGNAL(newConnection()),
           this,SLOT(newConnection()));
   mTcpSrv->listen(QHostAddress::Any,8081);
   QTimer* cleanupTimer = new QTimer(this);
   connect(cleanupTimer,SIGNAL(timeout()),
           this,SLOT(cleanPool()));
   cleanupTimer->start(CLEANUP_INTERVAL);

   mManager = new qrs::ServicesManager(this);
   qrs::PrintService* print_service = new qrs::PrintService(mManager);
   connect(print_service,SIGNAL(print(QString)),
           this,SLOT(print(const QString&)));
   connect(print_service,SIGNAL(quit()),
           qApp,SLOT(quit()));
}

void Server::newConnection() {
   QTcpSocket* socket = mTcpSrv->nextPendingConnection();
   if (socket == 0) return;
   qrs::DeviceManager* dmanager = new qrs::DeviceManager;
   connect(dmanager,SIGNAL(received(QByteArray)),
           mManager,SLOT(receive(const QByteArray&)));
   connect(mManager,SIGNAL(send(QByteArray)),
           dmanager,SLOT(send(const QByteArray&)));
   dmanager->setParent(socket);
   dmanager->setDevice(socket);
   mConnectionPool.append(socket);
}

void Server::cleanPool() {
   if ( mConnectionPool.isEmpty() ) return;
   QLinkedList<QTcpSocket*>::iterator indx = mConnectionPool.begin();
   while ( indx != mConnectionPool.end() ) {
      if ( ! (*indx)->isOpen() ) {
         delete *indx;
         indx = mConnectionPool.erase(indx);
         continue;
      }
      indx++;
   }
}

void Server::print(const QString& line) {
   QTextStream cout(stdout);
   cout << line << endl;
}
