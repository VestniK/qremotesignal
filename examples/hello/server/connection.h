/**
 * @file connection.h
 * @brief connection interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Nov 2009
 */
#ifndef Connection_H
#define Connection_H

#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>

#include <QRemoteSignal>

#include "helloservice.h"

class Connection : public QObject {
   Q_OBJECT
   public:
      Connection(QTcpSocket *socket, QObject *parent = 0);
      virtual ~Connection() {};
   private slots:
      void onSetName(const QString& name);
   private:
      qrs::HelloService *mService;
      static qrs::AbsMessageSerializer *serializer;
};

#endif
