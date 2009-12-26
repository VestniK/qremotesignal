/**
 * @file server.h
 * @brief Server interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#ifndef Server_h
#define Server_h

#include <QtCore/QObject>
#include <QtCore/QLinkedList>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>

#include <QRemoteSignal>

class Server : public QObject {
   Q_OBJECT
   public:
      Server(QObject *parent = 0);
      ~Server() {};
   public slots:
      void newConnection();
      void cleanPool();
      void print(const QString& line);
   private:
      QTcpServer* mTcpSrv;
      QLinkedList<QTcpSocket*> mConnectionPool;
      qrs::ServicesManager* mManager;
};

#endif
