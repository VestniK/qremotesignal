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
    * in this case ServicesManager takes ownership on the service and you don't
    * have to warry about deleting service instance.
    *
    * If this approach is not acceptable for your needs for some reasons you
    * can register your service with registerService function.
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
          * @return pointer to currently used serializer
          */
         AbsMessageSerializer *serializer();
         
         static void setDefaultSerializer(AbsMessageSerializer *serializer);
         static AbsMessageSerializer *defaultSerializer();

         /// @brief Add IO device to send receive data
         void addDevice(QIODevice* dev);
         /// @brief Returns number of the devices used to send/receive messages
         int devicesCount() const;
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
      private:
         Q_DISABLE_COPY(ServicesManager);
         internals::ServicesManagerPrivate *const d;
         
         static AbsMessageSerializer *mDefaultSerializer;
      private slots:
         /// @brief Called if device added by addDevice method is deleted
         void onDeviceDeleted(QObject* dev);
   };

}

#endif
