/**
 * @file servicesmanager.cpp
 * @brief ServicesManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "servicesmanager.h"

#include <QtCore/QPointer>
#include <QtCore/QSharedPointer>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QReadWriteLock>
#include <QtCore/QReadLocker>
#include <QtCore/QWriteLocker>

#include "qdatastreamserializer.h"
#include "devicemanager.h"
#include "absmessageserializer.h"
#include "absservice.h"

namespace qrs {
namespace internals {

class ServicesManagerPrivate {
public:
    QMap< QString, AbsService*> mServices;
    QList< QSharedPointer<DeviceManager> > mDevManagers;
    QPointer<AbsMessageSerializer> mSerializer;
    quint32 mMessageSizeLimit;
};

}
}

/**
 * @namespace qrs
 * @brief Main library namespace
 */
using namespace qrs;

AbsMessageSerializer *ServicesManager::mDefaultSerializer = 0;
QReadWriteLock defaultSerializerLocker;

/**
 * This static method allows you to set serializer which will be used by all
 * ServiceManager instances by default.
 *
 * This function is thread safe.
 *
 * @note Changing default serializer with this function will not affect earlier
 * created instances of the ServicesManager class.
 */
void ServicesManager::setDefaultSerializer(AbsMessageSerializer *serializer) {
    QWriteLocker locker(&defaultSerializerLocker);
    mDefaultSerializer = serializer;
}

/**
 * @return pointer to default serializer.
 *
 * @note Until setDefaultSerializer is not explicitly called this function will
 * always return 0 and all serializer instances will use QDataStreamSerializer
 * using data stream protocol of verion QDataStream::Qt_4_5.
 *
 * @sa ServicesManager::setDefaultSerializer
 */
AbsMessageSerializer *ServicesManager::defaultSerializer() {
    QReadLocker locker(&defaultSerializerLocker);
    return mDefaultSerializer;
}

/**
 * Constructs new ServicesManager object.
 *
 * By default new instance will use serializer set by the  static function
 * ServicesManager::setDefaultSerializer or QDataStreamSerializer with data
 * stream protocol version QDataStream::Qt_4_5 if default serializer wasn't
 * set explicitly.
 *
 * @note This constructor accesses global data in thread safe way.
 */
ServicesManager::ServicesManager(QObject *parent):
        QObject(parent),
        d(new internals::ServicesManagerPrivate)
{
    d->mMessageSizeLimit = 0;
    QReadLocker locker(&defaultSerializerLocker);
    if ( mDefaultSerializer == 0 ) {
        d->mSerializer = qDataStreamSerializer_4_5;
    } else {
        d->mSerializer = mDefaultSerializer;
    }
}

ServicesManager::~ServicesManager()
{
    delete d;
}

AbsMessageSerializer *ServicesManager::serializer()
{
    return d->mSerializer;
}

/**
 * This function sets serializer to be used to convert internal library message
 * representation into raw messages of some RPC protocol. Each serializer comes
 * with this library has single global instance of it which can be accessed
 * with macro. It's better to use this global instance instead of creating your
 * own instance and control its lifecicle.
 *
 * If you do want to create your own instance please remember that this
 * function will not take ownership on the instance given as parameter you have
 * to control your serializer delition manually.
 *
 * @sa AbsMessageSerializer
 */
void ServicesManager::setSerializer(AbsMessageSerializer *serializer)
{
    d->mSerializer = serializer;
}

int ServicesManager::devicesCount() const
{
    return d->mDevManagers.count();
}

/**
 * @param i index of the device you want to get. It should be between 0 and
 * devicesCount()
 */
QIODevice *ServicesManager::deviceAt(int i)
{
    return d->mDevManagers[i]->device();
}

/**
 * This function will not delete device itself it will just make this instance
 * of ServicesManager stop to use it for sending receiving messages. Device
 * even will not be closed.
 *
 * @param i index of the device you want to remove. It should be between 0 and
 * devicesCount()
 */
void ServicesManager::removeDevice(int i)
{
    d->mDevManagers.removeAt(i);
}

/**
 * @brief Removes device at the given index and returns pointer to it.
 *
 * This function only removes device from the list of devices to send receive
 * messages. Device is not deleted or closed.
 *
 * @param i index of the device to remove.
 */
QIODevice *ServicesManager::takeDeviceAt(int i)
{
    return d->mDevManagers.takeAt(i)->device();
}

/**
 * @brief Process received raw message
 *
 * This slot can be connected to some signal of class produces raw messages. It
 * process received message and calls corresponding service message processor.
 *
 * If message require to call a method from a service which is not registered
 * in this ServicesManager it sends error message by emiting send(QByteArray)
 * signal. Error message will be sent if a service which method is called can't
 * process the message received (no such method, wrong arguments or arguments
 * types).
 *
 * This slot do nothing if serializer to serialize/deserialize raw messages is
 * set to 0 pointer or was deleted.
 *
 * @sa send(QByteArray)
 * @sa AbsMessageSerializer
 *
 * @param msg received raw message
 */
void ServicesManager::receive(const QByteArray& msg)
{
    if ( !d->mSerializer ) {
        return;
    }
    MessageAP message;
    try {
        message = d->mSerializer->deserialize(msg);
    } catch (const MessageParsingException& e) {
        Message err;
        err.setType(Message::Error);
        err.setErrorType(e.mErrorType);
        err.setError( e.reason() );
        emit send( d->mSerializer->serialize(err) );
        emit clientError(this, err.errorType(), err.error());
        return;
    }
    if ( message->type() == Message::Error ) {
        emit error(this, message->errorType(), message->error());
        return;
    }
    QMap<QString,AbsService*>::iterator res = d->mServices.find(message->service());
    if ( res != d->mServices.end() ) {
        try {
            (*res)->processMessage(*message);
        } catch ( IncorrectMethodException& e ) {
            Message err;
            err.setType(Message::Error);
            err.setErrorType(Message::IncorrectMethod);
            err.setError(e.reason());
            err.setService(message->service());
            err.setMethod(message->method());
            emit send( d->mSerializer->serialize(err) );
            emit clientError(this, err.errorType(), err.error());
            return;
        }
    } else {
        Message err;
        err.setType(Message::Error);
        err.setErrorType(Message::UnknownService);
        err.setError(QString("Unknown service: \"%1\"").arg(message->service()));
        err.setService(message->service());
        emit send( d->mSerializer->serialize(err) );
        emit clientError(this, err.errorType(), err.error());
        return;
    }
}

/**
 * This function registers new service or client in this ServicesManager. If
 * service with the same name have been already registerd it replace old
 * service object with the new one.
 *
 * @note One instance of service can be registered only in one services
 * manager. If instance you are passing to this method is registered in another
 * services manager it will be automatically unregistered there.
 *
 * Service name is determined with AbsService::name() function.
 *
 * @sa AbsService
 *
 * @param service service or client instance to be registered.
 */
void ServicesManager::registerService(AbsService* service)
{
    if ( service->manager() != 0 ) {
        service->manager()->unregister(service);
    }
    d->mServices[service->name()] = service;
    service->setManager(this);
}

/**
 * @param name service or client name to unregister.
 *
 * Tthis function unregisters instance with the name given in parameter from
 * this services manager. If there is no client or service with theis name
 * registered in this manager it will do nothing.
 *
 * @return instance being unregistered or 0 if no instance with this name is
 * registered in this manager.
 *
 * If you are using Qt parent/child memory management mechanism you may want
 * to delete returned instance since in other case it will exists untill this
 * instance of ServicesManager class exits.
 */
AbsService *ServicesManager::unregister(const QString &name)
{
    QMap<QString, AbsService*>::iterator it = d->mServices.find(name);
    AbsService *res = 0;
    if ( it != d->mServices.end() ) {
        res = it.value();
        d->mServices.erase(it);
        res->setManager(0);
    }
    return res;
}

/**
 * @param instance service or client instance to be unregistered
 *
 * This function unregisters instance from this manager if it is registered in
 * other case it is doing nothing.
 */
void ServicesManager::unregister(AbsService *instance)
{
    QMap<QString, AbsService*>::iterator it = d->mServices.find(instance->name());
    if ( it != d->mServices.end() && it.value() == instance ) {
        d->mServices.erase(it);
        instance->setManager(0);
    }
}

/**
 * @return service with this name if such service is registered in this manager
 * instance or 0.
 */
AbsService *ServicesManager::service(const QString &name)
{
    return d->mServices.value(name,0);
}

/**
 * @internal
 *
 * This function provided to be used by client classes generated from service
 * interface description. You should not use this function manually. It can be
 * renamed or removed in future versions.
 */
void ServicesManager::send(const Message& msg)
{
    if ( !d->mSerializer ) return;
    emit send( d->mSerializer->serialize(msg) );
}

/**
 * Adds device to be used to send/receive raw messages. You may add several
 * devices to one ServicesManager instance. In this case any outgoing message
 * will be sent to all devices. If device is deleted it will be automatically
 * removed from the list of devices added by this function.
 *
 * @note You should add device to the ServicesManager instance only after you
 * have registered all services you are planning to use with this instance.
 * Otherwise if device already have some arrived messages they may be processed
 * incorrectly if destination service have not yet been registered.
 *
 * @param dev device to be used for sending/receiving messages
 */
void ServicesManager::addDevice(QIODevice *dev)
{
    foreach (const QSharedPointer<internals::DeviceManager> dm, d->mDevManagers) {
        if ( dm->device() == dev ) {
            return;
        }
    }
    QSharedPointer<internals::DeviceManager> dm(new internals::DeviceManager());
    dm->setMaxMessageSize(d->mMessageSizeLimit);
    connect( dm.data(), SIGNAL(received(QByteArray)),
             this, SLOT(receive(const QByteArray&)) );
    connect( this, SIGNAL(send(QByteArray)),
             dm.data(), SLOT(send(const QByteArray&)) );
    connect( dm.data(), SIGNAL(messageTooBig(qrs::internals::DeviceManager *)),
             this, SLOT(onMessageTooBig(qrs::internals::DeviceManager *)) );
    dm->setDevice(dev);
    d->mDevManagers.append(dm);
    connect( dev, SIGNAL(destroyed( QObject* )),
             this, SLOT(onDeviceDeleted(QObject*)) );
}

/**
 * @return current message size limit.
 * @sa setMessageSizeLimit(quint32)
 */
quint32 ServicesManager::messageSizeLimit() const
{
    return d->mMessageSizeLimit;
}

/**
 * This function is added to improve security of the applications using this
 * library. Devices which are used by ServicesManager can receive message that
 * is bigger then ammount of free RAM in this case application can crash.
 *
 * In order to protect your application from such issue you can specify limit
 * on the received message size with this function. Messages thet are bigger
 * then the given value will be discarded and device will be closed
 * immediatelly after sendig error message to the client. ServiceManager emits
 * the signal messageTooBig(QIODevice *) right after device is closed. You can
 * connect it to some slot in order to delete closed device (use deleteLater()
 * method for this).
 *
 * For backward compatibility default value for the limit is 0 which means no
 * message size limitation at all.
 *
 * @note This limit is used only for devices added with addDevice(QIODevice*)
 * method. It is not applied to the messages received by the slot
 * receive(const QByteArray &)
 *
 * @sa messageSizeLimit()
 * @sa messageTooBig(QIODevice *)
 */
void ServicesManager::setMessageSizeLimit(quint32 val)
{
    d->mMessageSizeLimit = val;
    foreach(QSharedPointer<internals::DeviceManager> dm, d->mDevManagers) {
        dm->setMaxMessageSize(val);
    }
}

/**
 * @internal
 *
 * This slot handles resources cleanup if one of the devices used by this
 * services manager to read write messages is deleted.
 */
void ServicesManager::onDeviceDeleted(QObject* dev)
{
    QList< QSharedPointer<internals::DeviceManager> >::iterator it;
    for ( it = d->mDevManagers.begin(); it != d->mDevManagers.end(); it++ ) {
        QObject *currentDev = (*it)->device();
        // DeviceManager stores QPointer instead of normal pointers and it can
        // know that dev is deleted before this slot is called. That's why I
        // should check that currentDev is non-zero.
        if ( !currentDev || currentDev == dev ) {
            d->mDevManagers.erase(it);
            return;
        }
    }
}

/**
 * @internal
 *
 * This slot handles closing device and sending notification if message which
 * is going to be sent is bigger then allowed limit.
 */
void ServicesManager::onMessageTooBig(internals::DeviceManager *source)
{
    Message err;
    err.setType(Message::Error);
    err.setErrorType(Message::ProtocolError);
    err.setError(QString("Message bigger then allowed limit '%1' bytes").arg(source->maxMessageSize()));
    emit send( d->mSerializer->serialize(err) );
    emit clientError(this, err.errorType(), err.error());
    source->device()->close();
    emit messageTooBig(source->device());
}
