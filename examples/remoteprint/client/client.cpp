/**
 * @file client.cpp
 * @brief client application start point
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#include <QtCore>
#include <QtDebug>

#include <QRemoteSignal>

#include "printclient.h"
#include "connectionprocessor.h"

int main(int argc,char **argv) {
   QCoreApplication app(argc,argv);

   QStringList args = app.arguments();
   if ( args.size() != 3 ) {
      qWarning() << "Ussage:\n\tprintclient host message";
      return -1;
   }

   QTcpSocket* socket = new QTcpSocket(&app);
   socket->connectToHost(args[1],8081);
   socket->waitForConnected();
   QObject::connect(socket,SIGNAL(disconnected()),
                    &app,SLOT(quit()));
   ConnectionProcessor* processor = new ConnectionProcessor(socket);

   qrs::ServicesManager* manager = new qrs::ServicesManager(&app);
   manager->setSerializer(new qrs::JsonSerializer(manager));
   qrs::PrintClient* client = new qrs::PrintClient(manager);

   QObject::connect(manager,SIGNAL(send(QByteArray)),
                    processor,SLOT(sendMessage(const QByteArray&)));
   QObject::connect(processor,SIGNAL(messageRecieved(QByteArray)),
                    manager,SLOT(recieve(const QByteArray&)));

   client->print(args[2]);
   return app.exec();
}
