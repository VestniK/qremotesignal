/**
 * @file client.cpp
 * @brief client application start point
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#include <QtCore>
#include <QtNetwork>
#include <QtDebug>

#include <QRemoteSignal>

#include "printclient.h"

int main(int argc,char **argv) {
   QCoreApplication app(argc,argv);

   QStringList args = app.arguments();
   if ( args.size() != 3 ) {
      qWarning() << "Ussage:";
      qWarning() << "Send message to a server";
      qWarning() << "\t" << argv[0] << " host message";
      qWarning() << "Shoutdown a server";
      qWarning() << "\t" << argv[0] << " host -q";;
      return -1;
   }

   QTcpSocket* socket = new QTcpSocket(&app);
   socket->connectToHost(args[1],8081);
   socket->waitForConnected();
   QObject::connect(socket,SIGNAL(disconnected()),
                    &app,SLOT(quit()));
   qrs::DeviceManager* dmanager = new qrs::DeviceManager;

   qrs::ServicesManager* manager = new qrs::ServicesManager(&app);
   manager->setSerializer(new qrs::JsonSerializer(manager));
   qrs::PrintClient* client = new qrs::PrintClient(manager);

   QObject::connect(manager,SIGNAL(send(QByteArray)),
                    dmanager,SLOT(send(const QByteArray&)));
   QObject::connect(dmanager,SIGNAL(received(QByteArray)),
                    manager,SLOT(receive(const QByteArray&)));
   dmanager->setParent(socket);
   dmanager->setDevice(socket);

   if ( QString("-q") == argv[2] ) {
      client->quit();
   } else {
      client->print(args[2]);
   }
   socket->close();
   return app.exec();
}
