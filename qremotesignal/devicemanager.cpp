/**
 * @file devicemanager.cpp
 * @brief DeviceManager implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Oct 2009
 */
#include "devicemanager.h"

using namespace qrs;
using namespace qrs::internals;

DeviceManager::DeviceManager(QObject *parent):
        QObject(parent)
{
    mMaxMessageSize = 0;
    mExpectedMessageSize = 0;
    mDevice = 0;
}

/**
 * @brief Constructs new device manager using given device for IO operations
 * @param device QIODevice to be used for input and output
 * @param parent Parent QObject
 *
 * This constructor uses setDevice method which emits deviceUnavailable signal
 * if device is not usable.
 *
 * @sa setDevice
 */
DeviceManager::DeviceManager(QIODevice *device, QObject *parent = 0):
        QObject(parent)
{
    mMaxMessageSize = 0;
    mExpectedMessageSize = 0;
    mDevice = 0;
    this->setDevice(device);
}

/**
 * @brief Set device to be used for IO operations
 * @param device QIODevice to be used for IO opearions
 *
 * This functions prepare DeviceManager to work with the device given. It emits
 * deviceUnavailable signal if null pointer is given as argument, if the device
 * given is not opened, not readable or not writable. It reads all data already
 * available for reading.
 *
 * Use null pointer as argument if you want unset previously set device.
 *
 * @sa deviceUnavailable
 */
void DeviceManager::setDevice(QIODevice* device)
{
    if (mDevice != 0) {
        disconnect(mDevice,SIGNAL(readyRead()),
                   this,SLOT(onNewData()));
        disconnect(mDevice,SIGNAL(readChannelFinished()),
                   this,SIGNAL(deviceUnavailable()));
        disconnect(mDevice,SIGNAL(destroyed( QObject* )),
                   this,SIGNAL(deviceUnavailable()));
    }
    mDevice = device;
    mExpectedMessageSize = 0;
    mBuffer.clear();
    mStream.setDevice(mDevice);
    mStream.setByteOrder(QDataStream::BigEndian);
    if (mDevice == 0) {
        emit deviceUnavailable();
        return;
    }
    if (!device->isOpen() || !device->isReadable() || !device->isWritable()) {
       emit deviceUnavailable();
    }
    connect(mDevice,SIGNAL(readyRead()),
            this,SLOT(onNewData()));
    connect(mDevice,SIGNAL(readChannelFinished()),
            this,SIGNAL(deviceUnavailable()));
    connect(mDevice,SIGNAL(destroyed( QObject* )),
            this,SIGNAL(deviceUnavailable()));
    if (mDevice->bytesAvailable() != 0) {
        onNewData();
    }
}

/**
 * @brief Sends message
 *
 * This function tries to send a message using QIODevice set by setDevice
 * function. If device was not set, is deleted or not opened for writing this
 * function emits deviceUnavailable signal.
 *
 * @sa setDevice
 * @sa deviceUnavailable
 */
void DeviceManager::send(const QByteArray& msg)
{
    if (mDevice == 0) {
        emit deviceUnavailable();
        return;
    }
    if (!mDevice->isWritable()) {
        emit deviceUnavailable();
        return;
    }
    if (msg.isNull()) {
        return;
    }
    mStream << msg;
}

void DeviceManager::onNewData()
{
    if (mDevice == 0) {
        emit deviceUnavailable();
        return;
    }
    if (!mDevice->isReadable()) {
        emit deviceUnavailable();
        return;
    }

    QDataStream reader(mDevice);
    while (reader.device()->bytesAvailable() > 0) {
        if (mBuffer.isEmpty() && mExpectedMessageSize == 0) {
            // Not enough data waiting for the next portion.
            if (reader.device()->bytesAvailable() < sizeof(quint32)) return;
            reader >> mExpectedMessageSize;
            // Zero sized message see Qt documentation for details
            if (mExpectedMessageSize == quint32(0xFFFFFFFF)) {
                mExpectedMessageSize = 0;
                continue;
            }
            mReceivedPartSize = 0;
            mBuffer.reserve(mExpectedMessageSize+1);
        }

        // If message is too big
        if (mMaxMessageSize > 0 && mExpectedMessageSize > mMaxMessageSize) {
            emit messageTooBig();
            return;
        }

        int bytesRead = reader.readRawData(
                mBuffer.data() + mReceivedPartSize,
                mExpectedMessageSize - mReceivedPartSize);
        if (bytesRead > 0) {
            mReceivedPartSize += bytesRead;
            mBuffer.resize(mReceivedPartSize);
        } else {
            /// @todo Do some IO error processing here
        }

        if (mReceivedPartSize == mExpectedMessageSize) {
            emit received(mBuffer);
            mBuffer.clear();
            mExpectedMessageSize = 0;
        }
    }
}
