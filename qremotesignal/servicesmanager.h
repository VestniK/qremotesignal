/**
 * @file servicesmanager.h
 * @brief ServicesManager class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _ServicesManager_H
#define _ServicesManager_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QByteArray>

#include "qrsexport.h"
#include "message.h"

// Forward declarations
class QIODevice;

namespace qrs {

   // Forward declarations
   namespace internals {
      class ServicesManagerPrivate;
      class DeviceManager;
   };
   class AbsMessageSerializer;
   class AbsService;

   /**
    * @brief Class managing communications between services and clients.
    *
    * This class is used by classes generated from XML remote interface
    * description to communicate with each other.
    *
    * Every service and client class generated from XML remote interface
    * description should be registered in a ServicesManager class instance.
    * ServicesManager sends and recieves raw messages and deliver them to
    * correct service classes. It also provides error messages handling.
    *
    * The simpliest way to register service or client class is to pass
    * pointer to ServicesManager instance to the service class constructor
    * @code
    * qrs::ServiceManager manager = new ServicesManager();
    * qrs::MyService service = new qrs::MyService(manager);
    * @endcode
    * in this case ServicesManager takes ownership on the service instance.
    *
    * If this approach is not suits your needs for some reason you can register
    * your service with ServicesManager::registerService function.
    *
    * There are two ways how to send and receive messages:
    * @li Using addDevice function to set device to be used to send/receive
    * messages. This class designed to work with sequential QIODevices (for
    * example QTcpSocket, QUdpSocket, QProcess).
    * @li Using receive slot to pass received message to the ServicesManager
    * and listening send signal to obtain raw messages to be sent. In this case
    * you need to write your own mechanism to send/receive raw messages.
    *
    * @sa @ref generated_classes
    */
   class QRS_EXPORT ServicesManager : public QObject {
      Q_OBJECT
      Q_DISABLE_COPY(ServicesManager);
      public:
         explicit ServicesManager(QObject *parent = 0);
         virtual ~ServicesManager();

         /// @brief Register service or client instance
         void registerService(AbsService *service);
         /// @brief Unregister service or client with given name
         AbsService *unregister(const QString &name);
         /// @brief Unregister service or client instance
         void unregister(AbsService *service);

         /// @brief Get registered service by name
         AbsService *service(const QString &name);

         void send(const Message& msg);

         void setSerializer(AbsMessageSerializer* val);
         /**
          * @return pointer to the currently used serializer
          */
         AbsMessageSerializer *serializer();

         static void setDefaultSerializer(AbsMessageSerializer *serializer);
         static AbsMessageSerializer *defaultSerializer();

         /// @brief Add IO device to send receive data
         void addDevice(QIODevice* dev);
         /// @brief Returns number of the devices used to send/receive messages
         int devicesCount() const;
         /// @brief Returns device used for cimunication by the index
         QIODevice *deviceAt(int i);
         /**
          * @brief Removes device at given position from list of devices used
          * for sending receiving messages.
          */
         void removeDevice(int i);
         QIODevice *takeDeviceAt(int i);

         /// @brief %Message size limit for devices added with addDevice method
         quint32 messageSizeLimit() const;
         /// @brief %Message size limit for devices added with addDevice method
         void setMessageSizeLimit(quint32 val);
      public slots:
         void receive(const QByteArray& msg);
      signals:
         /**
          * This signal is emited when a message should be sent.
          */
         void send(QByteArray msg);
         /**
          * This signal is emmited if error message received.
          */
         void error(qrs::ServicesManager *sender,
                    qrs::Message::ErrorType error,
                    QString description);
         /**
          * This signal is emmited before sending error message in response on
          * incorrect incomming protocol message.
          */
         void clientError(qrs::ServicesManager *sender,
                          qrs::Message::ErrorType error,
                          QString description);
         /**
          * This signal is sent if one of the devices added with the
          * addDevice(QIODevice *) method is bigger then allowed message size
          * limit. The message causing this error is not read. At the moment
          * this signal emitted the device is already closed.
          *
          * One of the possible reactions on this segnal is to call
          * deleterLater() method of the device.
          *
          * @param device device which received message causing this error.
          */
         void messageTooBig(QIODevice *device);
      private:
         internals::ServicesManagerPrivate *const d;

         static AbsMessageSerializer *mDefaultSerializer;
      private slots:
         /// @brief Called if device added by addDevice method is deleted
         void onDeviceDeleted(QObject* dev);
         /// @brief Called if device added by the addDevice method received too big message
         void onMessageTooBig(qrs::internals::DeviceManager *source);
   };

}

#endif
