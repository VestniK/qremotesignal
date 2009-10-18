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

#include "qrsexport.h"

namespace qrs {

   class QRS_EXPORT DeviceManager : public QObject {
      Q_OBJECT
      public:
         DeviceManager(QObject *parent = 0): QObject(parent) {mDevice = 0;};
         DeviceManager(QIODevice *device, QObject *parent);
         ~DeviceManager() {};

         const QIODevice* device() const {return mDevice;};
         QIODevice* device() {return mDevice;};
         void setDevice(QIODevice* device);
      public slots:
         void send(const QByteArray& msg);
      signals:
         void received(QByteArray msg);
      private slots:
         void onNewData();
      private:
         QPointer<QIODevice> mDevice;
         QDataStream mStream;
         QByteArray mBuffer;
   };

}

#endif
