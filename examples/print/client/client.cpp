/**
 * @file client.cpp
 * @brief client application start point
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#include <QtCore/QCoreApplication>
#include <QtCore/QStringList>
#include <QtNetwork/QTcpSocket>
#include <QtCore/QtDebug>

#include <QRemoteSignal>

#include "printclient.h"

int main(int argc,char **argv) {
   QCoreApplication app(argc,argv);

   QStringList args = app.arguments();
   if ( args.size() != 3 ) {
      qWarning() << "Ussage:";
      qWarning() << "Send message to a server";
      qWarning() << "\t" << args[0] << " host message";
      qWarning() << "Shoutdown a server";
      qWarning() << "\t" << args[0] << " host -q";;
      return -1;
   }

   QTcpSocket* socket = new QTcpSocket(&app);
   socket->connectToHost(args[1],8081);
   if ( !socket->waitForConnected() ) {
       qFatal("Can't connect to host '%s'",argv[1]);
   }
   QObject::connect(socket,SIGNAL(disconnected()),
                    &app,SLOT(quit()));

   qrs::ServicesManager* manager = new qrs::ServicesManager(&app);
   qrs::PrintClient* client = new qrs::PrintClient(manager);
   manager->addDevice(socket);

   if ( QString("-q") == args[2] ) {
      client->quit();
   } else {
      client->print(args[2]);
   }
   socket->close();
   return app.exec();
}
