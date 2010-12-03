/**
 * @file devicemanager.h
 * @brief devicemanager interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Oct 2009
 */
#ifndef _DeviceManager_H
#define _DeviceManager_H

#include <QtCore/QtGlobal>
#include <QtCore/QObject>
#include <QtCore/QIODevice>
#include <QtCore/QByteArray>
#include <QtCore/QPointer>
#include <QtCore/QDataStream>

#include "qrsexport.h"

namespace qrs {
namespace internals {

/**
 * @internal
 *
 * @deprecated use ServicesManager::addDevice(QIODevice *) instead.
 *
 * This class is removed from  the library public interface you should use
 * ServicesManager::addDevice(QIODevice *) instead.
 */
class DeviceManager : public QObject {
Q_OBJECT
Q_DISABLE_COPY(DeviceManager);
public:
    /**
     * @brief Default constructor
     *
     * Constructs device manager handling no device. Use setDevice to set
     * device to read and write messages.
     */
    explicit DeviceManager(QObject *parent = 0);
    DeviceManager(QIODevice *device, QObject *parent);
    ~DeviceManager() {};

    /// Returns QIODevice used for IO operations.
    const QIODevice* device() const {return mDevice;};
    /// Returns QIODevice used for IO operations.
    QIODevice* device() {return mDevice;};
    void setDevice(QIODevice* device);

    /**
     * @sa mMaxMessageSize
     */
    void setMaxMessageSize(quint32 val) {mMaxMessageSize = val;}
    /**
     * @sa mMaxMessageSize
     */
    quint32 maxMessageSize() const {return mMaxMessageSize;}
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
    /**
     * This signal is emitted when size of the message received is greater
     * then value specified by the mMaxMessageSize property.
     */
    void messageTooBig();
private slots:
    void onNewData();
private:
    QPointer<QIODevice> mDevice;
    QDataStream mStream;
    QByteArray mBuffer;
    quint32 mExpectedMessageSize;
    quint32 mReceivedPartSize;
    /**
     * Maximu for the size of received message. If reported size of the
     * received message is greater than this value message will not be
     * read.
     *
     * Default value 0 means no message size limitation.
     */
    quint32 mMaxMessageSize;
};

} // namespace internals
} // namespace qrs

#endif
