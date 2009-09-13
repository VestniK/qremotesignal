/**
 * @file connectionprocessor.cpp
 * @brief ConnectionProcessor implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 12 Sep 2009
 */
#include "connectionprocessor.h"

#include <QtDebug>

#define CONNECTION_TIMEOUT 1000 //ms
#define MAX_MEASSGE_SIZE 4096 // 4Kb

ConnectionProcessor::ConnectionProcessor(QTcpSocket *parent):QObject(parent) {
   mSocket = parent;
   connect(mSocket,SIGNAL(readyRead()),
           this,SLOT(readData()));
   QTimer::singleShot(CONNECTION_TIMEOUT,this,SLOT(timeout()));
   mMsgLength = -1;
}

void ConnectionProcessor::readData() {
   mReadBuf += mSocket->readAll();
   if ( mReadBuf.size() > MAX_MEASSGE_SIZE ) {
      qWarning() << "Error: ConnectionProcessor: incoming message too big. Closing connection." << endl;
      mSocket->abort();
      return;
   }
   int delimeterPos = mReadBuf.indexOf('\0');
   if ( mMsgLength < 0 && delimeterPos != -1 ) {
      bool ok = false;
      mMsgLength = mReadBuf.left(delimeterPos).toInt(&ok);
      if ( !ok ) {
         qWarning() << "Error: ConnectionProcessor: incorrect message. Can't obtain message length" << endl;
         mSocket->abort();
         return;
      }
   } else {
         return;
   }
   if ( mReadBuf.size() - (delimeterPos + 1) == mMsgLength ) {
      emit messageReceived(mReadBuf.right(mMsgLength));
      mMsgLength = -1;
      mReadBuf.clear();
      mSocket->close();
   }
}

void ConnectionProcessor::timeout() {
   mSocket->close();
}

void ConnectionProcessor::sendMessage(const QByteArray& msg) {
   if ( mSocket->state() == QAbstractSocket::ConnectedState ) {
      QByteArray message;
      message.setNum(msg.size());
      message.append('\0');
      message.append(msg);
      mSocket->write(message);
   } else {
      qWarning() << "Error: ConnectionProcessor::sendMessage(): Socket is closed" << endl;
   }
}
