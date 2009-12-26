/**
 * @file connection.cpp
 * @brief Connection implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#include "connection.h"

#include <QtCore/QCoreApplication>

#include <QRemoteSignal>

Connection::Connection (QTcpSocket *socket, QObject *parent):QObject(parent) {
   socket->setParent(this);
   connect(socket,SIGNAL(disconnected()),
           this,SLOT(deleteLater()));

   qrs::ServicesManager *manager = new qrs::ServicesManager(this);
   mService = new qrs::HelloService(manager);
   connect(mService,SIGNAL(setName(QString)),
           this,SLOT(onSetName(const QString&)));
   connect(mService,SIGNAL(quit()),
           qApp,SLOT(quit()));

   manager->addDevice(socket);
}

void Connection::onSetName(const QString &name) {
   mService->hello( QString("Hello %1").arg(name) );
}
