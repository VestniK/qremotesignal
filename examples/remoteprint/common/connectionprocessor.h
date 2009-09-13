/**
 * @file connectionprocessor.h
 * @brief ConnectionProcessor interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#ifndef connectionprocessor_h
#define connectionprocessor_h

#include <QtCore>
#include <QtNetwork>

class ConnectionProcessor : public QObject {
   Q_OBJECT
   public:
      ConnectionProcessor(QTcpSocket *parent = 0);
      ~ConnectionProcessor() {};
   public slots:
      void readData();
      void sendMessage(const QByteArray& msg);
      void timeout();
   signals:
      void messageReceived(QByteArray msg);
   private:
      QTcpSocket* mSocket;
      QByteArray mReadBuf;
      int mMsgLength;
};

#endif
