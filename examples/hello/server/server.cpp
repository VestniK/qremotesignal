/**
 * @file server.cpp
 * @brief Server implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#include "server.h"

#include "connection.h"

Server::Server(quint32 port, QObject *parent):QObject(parent) {
   mTcpServer = new QTcpServer(this);
   connect(mTcpServer,SIGNAL(newConnection()),
            this,SLOT(onNewConnection()));
   mTcpServer->listen(QHostAddress::Any,port);
}

void Server::onNewConnection() {
   QTcpSocket *socket = mTcpServer->nextPendingConnection();
   if ( socket == 0 ) {
      return;
   }
   Connection *connection = new Connection(socket,this);
}
