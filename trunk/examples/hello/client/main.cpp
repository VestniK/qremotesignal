/**
 * @file main.cpp
 * @brief Hello example client main function
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>

#include <QtCore/QtDebug>
#include <QtNetwork/QTcpSocket>

#include "client.h"

const int CONNECTION_TIMEOUT = 30000;

int main(int argc, char** argv) {
   QCoreApplication app(argc,argv);
   QStringList args = app.arguments();
   if ( args.count() != 3 ) {
      qDebug() << "Ussage:";
      qDebug() << "\t" << args[0] << "host your_name";
      return 1;
   }
   QTcpSocket *socket = new QTcpSocket();
   QObject::connect(socket,SIGNAL(disconnected()),
                    qApp,SLOT(quit()));
   socket->connectToHost(args[1],8081);
   if ( ! socket->waitForConnected(CONNECTION_TIMEOUT) ) {
      qDebug() << "Could not connect to host" << args[1];
      qDebug() << socket->errorString();
      return 1;
   }
   Client client(socket);
   if ( args[2] == "-q" ) {
      client.hello()->quit();
   } else {
      client.hello()->setName(args[2]);
   }
   return app.exec();
}
