/**
 * @file server.h
 * @brief server interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#ifndef Server_H
#define Server_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpServer>

class Server : public QObject {
   Q_OBJECT
   public:
      Server (quint32 port, QObject *parent = 0);
      virtual ~Server() {};
   private slots:
      void onNewConnection();
   private:
      QTcpServer *mTcpServer;
};

#endif
