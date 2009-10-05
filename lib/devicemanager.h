/**
 * @file devicemanager.h
 * @brief devicemanager interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Oct 2009
 */
#ifndef _DeviceManager_H
#define _DeviceManager_H

#include <QtCore>

namespace qrs {

   class DeviceManager : public QObject {
      Q_OBJECT
      public:
         DeviceManager(QObject *parent = 0): QObject(parent) {mDevice = 0;};
         DeviceManager(QIODevice *device, QObject *parent);
         ~DeviceManager() {};

         const QIODevice* device() const {return mDevice;};
         QIODevice* device() {return mDevice;};
         void setDevice(QIODevice* device);
      public slots:
         void sendMessage(const QByteArray& msg);
      signals:
         void messageReceived(QByteArray msg);
      private slots:
         void onNewDataReceived();
      private:
         QIODevice *mDevice;
         QDataStream mStream;
         QByteArray mBuffer;
   };

}

#endif
