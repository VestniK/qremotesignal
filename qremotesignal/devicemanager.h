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

   /**
    * @brief Class to manage messages delivery using QIODevice
    *
    * @todo write detailed documentation.
    */
   class QRS_EXPORT DeviceManager : public QObject {
      Q_OBJECT
      public:
         /**
          * @brief Default constructor
          *
          * Constructs device manager handling no device. Use setDevice to set
          * device to read and write messages.
          */
         explicit DeviceManager(QObject *parent = 0): QObject(parent) {mDevice = 0;};
         DeviceManager(QIODevice *device, QObject *parent);
         ~DeviceManager() {};

         /// Returns QIODevice used for IO operations.
         const QIODevice* device() const {return mDevice;};
         /// Returns QIODevice used for IO operations.
         QIODevice* device() {return mDevice;};
         void setDevice(QIODevice* device);
      public slots:
         void send(const QByteArray& msg);
      signals:
         /**
          * @param msg received message
          *
          * This signal is emitted if new message is received.
          */
         void received(QByteArray msg);
         /**
          * This signal emited if:
          * @li Device object is deleted
          * @li In case of attempt to send message while device is not writable
          * @li Device object is closed for reading
          */
         void deviceUnavailable();
      private slots:
         void onNewData();
      private:
         Q_DISABLE_COPY(DeviceManager);
         QPointer<QIODevice> mDevice;
         QDataStream mStream;
         QByteArray mBuffer;
   };

}

#endif
