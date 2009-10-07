/**
 * @file devicemanager.cpp
 * @brief $MODLE$ implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Oct 2009
 */
#include "devicemanager.h"

using namespace qrs;

DeviceManager::DeviceManager(QIODevice *device, QObject *parent = 0):QObject(parent) {
   mDevice = 0;
   this->setDevice(device);
}

void DeviceManager::setDevice(QIODevice* device) {
   if ( device != 0 ) {
      if ( ! device->isOpen() ) {
         /// @todo throw exception here! Device should be opened
      }
      if ( ! device->isReadable() ) {
         /// @todo throw exception here! Device should be readable
      }
      if ( ! device->isWritable() ) {
         /// @todo throw exception here! Device should be writable
      }
   }
   if ( mDevice != 0 ) {
      disconnect(mDevice,SIGNAL(readyRead()),
                 this,SLOT(onNewDataReceived()));
   }
   mDevice = device;
   mStream.setDevice(mDevice);
   mStream.setByteOrder(QDataStream::BigEndian);
   if ( mDevice == 0 ) {
      return;
   }
   connect(mDevice,SIGNAL(readyRead()),
           this,SLOT(onNewDataReceived()));
   // If device already contains some data then read it
   onNewDataReceived();
}

void DeviceManager::sendMessage(const QByteArray& msg) {
   if ( mDevice == 0 ) {
      return;
   }
   if ( msg.isNull() ) {
      return;
   }
   mStream << msg;
}

void DeviceManager::onNewDataReceived() {
   if ( mDevice == 0 ) {
      return;
   }
   mBuffer += mDevice->readAll();
   QDataStream buffReader(mBuffer);
   int pos = 0;
   while( !buffReader.atEnd() ) {
      QByteArray msg;
      buffReader >> msg;
      if ( buffReader.status() != QDataStream::Ok ) {
         break;
      }
      pos = buffReader.device()->pos();
      emit messageReceived(msg);
   }
   if ( pos != 0 ) {
      mBuffer = mBuffer.mid(pos);
   }
}
