/**
 * @file client.cpp
 * @brief Client implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#include "client.h"

#include <QtCore/QtDebug>
#include <QtNetwork/QTcpSocket>

#include <QRemoteSignal>

#include "helloclient.h"

Client::Client(QTcpSocket *socket, QObject *parent ):QObject(parent) {
   socket->setParent(this);
   mSocket = socket;

   qrs::ServicesManager *manager = new qrs::ServicesManager(this);
   mClient = new qrs::HelloClient(manager);
   connect(mClient,SIGNAL(hello(QString)),
           this,SLOT(onHello(const QString &)));

   manager->addDevice(mSocket);
}

void Client::onHello(const QString &greetings) {
   qDebug() << greetings;
   mSocket->close();
}
