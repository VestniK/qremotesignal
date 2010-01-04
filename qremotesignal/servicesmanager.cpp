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

#include "jsonserializer.h"
#include "devicemanager.h"
#include "absmessageserializer.h"
#include "absservice.h"

namespace qrs {
   namespace internals {

      class ServicesManagerPrivate {
         public:
            QMap< QString, AbsService*> mServices;
            QPointer<AbsMessageSerializer> mSerializer;
            QList< QSharedPointer<DeviceManager> > mDevManagers;
      };

   }
}

using namespace qrs;

/**
 * Constructs new ServicesManager object. By default it will use JsonSerializer
 * you can use setSerializer function to change it. Also you can define
 * DEFAULT_SERIALIZER macro which will be used to set default serializer.
 */
ServicesManager::ServicesManager(QObject *parent):
      QObject(parent),
      d(new internals::ServicesManagerPrivate) {
#ifdef DEFAULT_SERIALIZER
   d->mSerializer = DEFAULT_SERIALIZER;
#else
   d->mSerializer = jsonSerializer;
#endif
}

ServicesManager::~ServicesManager() {
   delete d;
}

AbsMessageSerializer *ServicesManager::serializer() {
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
void ServicesManager::setSerializer(AbsMessageSerializer *serializer) {
   d->mSerializer = serializer;
}

int ServicesManager::devicesCount() const {
   return d->mDevManagers.count();
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
void ServicesManager::receive(const QByteArray& msg) {
   if ( !d->mSerializer ) {
      return;
   }
   MessageAP message;
   try {
      message = d->mSerializer->deserialize(msg);
   } catch (const MessageParsingException& e) {
      Message err;
      err.setErrorType(e.mErrorType);
      err.setError( e.reason() );
      emit d->mSerializer->serialize(err);
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
         err.setErrorType(Message::IncorrectMethod);
         err.setError(e.reason());
         err.setService(message->service());
         err.setMethod(message->method());
         emit send( d->mSerializer->serialize(err) );
         return;
      }
   } else {
      Message err;
      err.setErrorType(Message::UnknownService);
      err.setError(QString("Unknown service: \"%1\"").arg(message->service()));
      err.setService(message->service());
      emit send( d->mSerializer->serialize(err) );
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
void ServicesManager::registerService(AbsService* service) {
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
AbsService *ServicesManager::unregister(const QString &name) {
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
void ServicesManager::unregister(AbsService *instance) {
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
AbsService *ServicesManager::service(const QString &name) {
   return d->mServices.value(name,0);
}

/**
 * @internal
 *
 * This function provided to be used by client classes generated from service
 * interface description. You should not use this function manually. It can be
 * renamed or removed in future versions.
 */
void ServicesManager::send(const Message& msg) {
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
void ServicesManager::addDevice(QIODevice* dev) {
   foreach (const QSharedPointer<internals::DeviceManager> dm, d->mDevManagers) {
      if ( dm->device() == dev ) {
         return;
      }
   }
   QSharedPointer<internals::DeviceManager> dm( new internals::DeviceManager() );
   connect(dm.data(),SIGNAL(received(QByteArray)),
           this,SLOT(receive(const QByteArray&)));
   connect(this,SIGNAL(send(QByteArray)),
           dm.data(),SLOT(send(const QByteArray&)));
   dm->setDevice(dev);
   d->mDevManagers.append(dm);
   connect(dev,SIGNAL(destroyed( QObject* )),
           this,SLOT(onDeviceDeleted(QObject*)));
}

/**
 * @internal
 *
 * This slot handles resources cleanup if one of the devices used by this
 * services manager to read write messages is deleted.
 */
void ServicesManager::onDeviceDeleted(QObject* dev) {
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
 * @mainpage
 *
 * @li @ref tutorial
 * @li @ref services_concept
 * @li @ref qrsc
 * @li @ref converters
 *
 * @section changelog Changelog
 *
 * @verbinclude ChangeLog
 */

/// @example hello/services/hello.xml

/// @example hello/server/main.cpp
/// @example hello/server/server.h
/// @example hello/server/server.cpp
/// @example hello/server/connection.h
/// @example hello/server/connection.cpp

/// @example hello/client/main.cpp
/// @example hello/client/client.h
/// @example hello/client/client.cpp

/**
 * @page tutorial Tutorial
 *
 * This article provides step by step tutorial of creation client-server
 * applications with the QRemoteSignal library. You can find compleate source
 * code of the example application described here in the @e examples/hello
 * directory of the libbrary source package.
 *
 * @section hello_service Application remote interface
 *
 * Lets create simple client-server application. The client can connect to the
 * server and send a name. The server will send the string "Hello "+name in
 * response on the message from client.
 *
 * First of all we need to create some services describing server remote
 * interface. For our small server it will be enough to have only one service.
 * Lets create XML file with the name @b hello.xml with the following content:
 * @dontinclude hello/services/hello.xml
 * @line service
 * @skip slot
 * @until /slot
 * @skip signal
 * @until service
 * It contains one slot @b setName which allows our client to send a name to
 * the server and one signal @b hello which allows our server to send greetings
 * string to our client.
 *
 * Now we can generate C++ classes which we can use in our application (see
 * @ref code_generation for details). We can do it with the following commands:
 * @code
 * qrsc --service --header helloservice.h --source helloservice.cpp hello.xml
 * qrsc --client --header helloclient.h --source helloclient.cpp hello.xml
 * @endcode
 * Or we can write some build script which will invoke this commands from build
 * system (some help on this topic you can find in @ref build_systems document).
 *
 * We will get 4 files:
 * @li @b helloservice.h and @b helloservice.cpp which we will use in the
 * server application.
 * @li @b helloclient.h and @b helloclient.cpp which we will use in the
 * client application.
 *
 * @section hello_server Server application
 *
 * Our server application will contain Server class which creates QTcpServer
 * listening some port and processing new incomming connections. After new
 * connection established it creates Connection class instance which will work
 * with the socket. This instance will be deleted if socket is disconnected.
 *
 * Main function and Server class contain no QRemoteSignal specific code it's
 * just usual QtNetwork library ussage. Here is the code:
 * @li @link hello/server/main.cpp server/main.cpp @endlink
 * @li @link hello/server/server.h server/server.h @endlink
 * @li @link hello/server/server.cpp server/server.cpp @endlink
 *
 * All magick is done in the @b Connection class. First of all in its
 * constructor we should create qrs::ServicesManager class instance. Then we
 * can create @b HelloService class instance and register it in our services
 * manager:
 * @dontinclude hello/server/connection.cpp
 * @skip new qrs::ServicesManager
 * @until new qrs::HelloService
 * Now @b mService instance also become a child of @b manager instance and will
 * be deleted if @b manager is deleted. QRemoteSignal library actively uses Qt4
 * memory management features to simplify memory management in you application.
 * Constructor generated for the @b HelloService class which takes pointer to a
 * qrs::ServicesManager class instance automatically registers newly created
 * @b HelloService instace in the qrs::ServicesManager instance passed to it
 * and set this manager instance to be its parent.
 *
 * Now we need to connect @b HelloService signals and slots to some signal and
 * slots in our application to provide meaningfull reaction on incomming
 * requests. For our small server it's enough to provide one slot which will
 * be connected to @b HelloService::setName signal. This slot will call
 * @b HelloService::hello slot with greetings string:
 * @dontinclude hello/server/connection.cpp
 * @skip Connection::onSetName
 * @until }
 *
 * And in the @b Connection class constructor we need to connect @b setName
 * signal to this slot right after @b HelloService instance creation:
 * @dontinclude hello/server/connection.cpp
 * @skip SIGNAL(setName
 * @until SLOT(onSetName
 * @endcode
 *
 * After that we need add socket to the list of devices used by @b manager for
 * sending/receiving raw messages:
 * @dontinclude hello/server/connection.cpp
 * @skipline addDevice
 *
 * Lets take a look on compleate @b Connection class code:
 * @li connection.h
 * @include hello/server/connection.h
 * @li connection.cpp
 * @dontinclude hello/server/connection.cpp
 * @skip #
 * @until SLOT(onSetName
 * @skip addDevice
 * @until }
 * @until }
 *
 * Server application is ready!
 *
 * @section hello_client Client application
 *
 * Our client application will be simple console application which takes two
 * command line parameters: host to connect to and your name. It sends your
 * name to the server, and waits for @b hello signal from the server. Once this
 * signal is received it prints received string and stops.
 *
 * Lets create @b Client class which takes connected socket in constructor and
 * creates qrs::ServicesManager using this socket to send/receive raw messages.
 * Also this class will have @b onHello slot which will listen for a @b hello
 * signal from the server. This class is similair to @b Connection class in the
 * server. Here is its code:
 * @li client.h
 * @include hello/client/client.h
 * @li client.cpp
 * @include hello/client/client.cpp
 *
 * We have created qrs::ServicesManager instance, created @b HelloClient
 * instance and registered it in manager, connected @b hello signal to slot
 * providing meaningfull reaction on incoming message everything like in the
 * @b Connection class of the server application.
 *
 * In our main function we will check command line arguments, connect to the
 * server, create @b Client class instance and send the name to the server:
 * @li main.cpp
 * @dontinclude hello/client/main.cpp
 * @skip #
 * @until client(socket)
 * @skipline setName
 * @skip return
 * @until }
 *
 * Now our client applicaion ready! Lets run the server and and try it:
 * @code
 * vestnik@vestnik-laptop:~/Development/QRemoteSignal/examples$ ./hello/client/client localhost VestniK
 * "Hello VestniK"
 * vestnik@vestnik-laptop:~/Development/QRemoteSignal/examples$
 * @endcode
 *
 * @section extending_hello Extending example with more slots
 *
 * The most important thing I'm trying to implement in the QRemoteSignal
 * library is simple extesibility of client server applications with new remote
 * callable slots. Lets extend our application with one new function to see how
 * simple it to do.
 *
 * It's a bit annoying to search your server in the processes list and kill.
 * Lets add ability to shoutdown server application from the client (sure it's
 * not secure but this is simple "hello world" example).
 *
 * First of all we need to add one more slot to the @b hello.xml file:
 * @dontinclude hello/services/hello.xml
 * @skipline quit
 * It takes no parameters and just shoutdown the server.
 *
 * Now we need to regenerate @b HelloService and @b HelloClient classes and
 * connect @b HelloService::quit signal to @b qApp->quit slot in the
 * @b Connection class constructor. Lets add the following lines after
 * @b HelloService instance creation:
 * @dontinclude hello/server/connection.cpp
 * @skip SIGNAL(quit
 * @until qApp
 *
 * Server now provides support of remote shoutdown feature!
 *
 * Lets modify our client to use this feature. We will just replece this line
 * in the main.cpp file of the client application:
 * @dontinclude hello/client/main.cpp
 * @skipline client.hello()->setName
 * With this several lines:
 * @dontinclude hello/client/main.cpp
 * @skip if ( args[2] == "-q" )
 * @until }
 * @until }
 * and that's all we have to do!
 *
 * @section files_list Full example sources
 *
 * Service:
 * @li @link hello/services/hello.xml services/hello.xml @endlink
 *
 * Server:
 * @li @link hello/server/main.cpp server/main.cpp @endlink
 * @li @link hello/server/server.h server/server.h @endlink
 * @li @link hello/server/server.cpp server/server.cpp @endlink
 * @li @link hello/server/connection.h server/connection.h @endlink
 * @li @link hello/server/connection.cpp server/connection.cpp @endlink
 *
 * Client:
 * @li @link hello/client/main.cpp client/main.cpp @endlink
 * @li @link hello/client/client.h client/client.h @endlink
 * @li @link hello/client/client.cpp client/client.cpp @endlink
 */

/**
 * @page qrsc XML service description
 *
 * Slots you want to call remotely should be described in an XML file which
 * will be used to generate C++ classes you can use in your application. One
 * XML file describes one service (see @ref services_concept for details about
 * services).
 *
 * @section schema File format
 *
 * Here is a simple example of service XML description:
 * @code
 * <service name="Example">
 *    <customtypes header="customtypesconverters.h"/>
 *    <slot name="mySlot">
 *       <param name="num" type="qint32"/>
 *    </slot>
 *    <signal name="mySignal">
 *       <param name="str" type="QString"/>
 *    </signal>
 * </service>
 * @endcode
 *
 * @li Root element @b service must have @b name attribute with a service name.
 *
 * @li You can have any number of @b customtypes elements with @b header
 * attribute specifying C++ header file with convertors functions for your
 * custom types (see @ref converters for details). This header is included in
 * the *.h files with the interface of the service and cient classes.
 *
 * @li @b slot element describes slot which can be called remotelly. Attribute
 * @b name specifies the name of this slot. This element can have any number of
 * child @b param elements.
 *
 * @li @b signal element describes signal which can be emited to remote
 * application. Attribute @b name specifies the name of this signal. This
 * element can have any number of child @b param elements.
 *
 * @li @b param element is used inside @b signal and @b slot elements to
 * describe signal or slot parameter. It has two attributes @b type which
 * specifies C++ type of the corresponding signal or slot argument and
 * @b name which specifies parameter name. Both of this attributes are
 * obligitary.
 *
 * @section code_generation C++ code generation with qrsc utility
 *
 * Once you've described your application remote interface in XML files you can
 * generate classes which you can use in your application. You can do this with
 * @b qrsc application (qrsc is abbriviation for QRemoteSignal compiler).
 *
 * To generate a @e Sevice class (the one to be used in a server application)
 * use the following command:
 * @code
 * qrsc --service --header exampleservice.h --source exampleservice.cpp example.xml
 * @endcode
 * it will create two files @b exampleservice.h and @b exampleservice.cpp
 * with declaration and implementation of class describing your service.
 *
 * To generate a @e Client class (the one to be use in a client application)
 * use the following command:
 * @code
 * qrsc --client --header exampleclient.h --source exampleclient.cpp example.xml
 * @endcode
 * it will create two files @b exampleclient.h and @b exampleclient.cpp with
 * declaration and implementation of class describing interface for calling
 * your service slots and reciving its signals from the client application.
 *
 * You can find more information about @b qrsc in its unix man page or by
 * running
 * @code
 * qrsc --help
 * @endcode
 *
 * @note If you have interface files for the version 0.6.0 of the QRemoteSignal
 * library or older you should rename all @b method elements to @b slot or run
 * @code
 * qrsc --update new_file.xml old_file.xml
 * @endcode
 * to do it automatically. You still can use your old interface with the new
 * version of @b qrsc utility but it will print warning message about outdated
 * format of your service.
 *
 * @section generated_classes Using generated classes in your application
 *
 * Classes generated from XML interface description can be used to call slots
 * and emit signals between different application.
 *
 * First of all you need to register instances of generated class in a
 * qrs::ServicesManager class instance (see this class documentation for
 * detales). After your service or client class is registered in manager
 * you can connect signals and slots it has to you application classes
 * signals and slots. Each time you call a slot in generated class
 * services manager sends a message to another application to call
 * corresponding signal in it.
 *
 * @subsection generated_service Using generated class in the server application.
 *
 * Here is public signals and slots of the service class generated from the
 * example XML file you can find in the beggining of this page:
 * @code
 * namespace qrs {
 *
 *    class ExampleService: public AbsService {
 *       ...
 *       public slots:
 *          void mySignal(const QString &str);
 *       signals:
 *          void mySlot(const quint32 &num);
 *    };
 *
 * }
 * @endcode
 *
 * Each time you server receives request to call slot @b mySlot instance of
 * this class emits signal @b mySlot you can connect it to any slot in you
 * application to provide meaningfull reaction on this event.
 *
 * Each time you want your server to emit remote signal @b mySignal you need
 * to call @b mySignal slot and you server sends request to the client
 * application to call necessary function.
 *
 * @subsection generated_client Using generated class in the client application.
 *
 * Here is public signals and slots of the client class generated from the
 * example XML file you can find in the beggining of this page:
 * @code
 * namespace qrs {
 *
 *    class ExampleClient: public AbsService {
 *       ...
 *       public slots:
 *          void mySlot(const quint32 &num);
 *       signals:
 *          void mySignal(const QString &str);
 *    };
 *
 * }
 * @endcode
 *
 * Each time you call slot @b mySlot you client application sends to your
 * server application request to call corresponding function.
 *
 * Each time your server application sends signal @b mySignal to you client
 * application signal @b mySignal is emitted. You can connect this signal to
 * some slot in your class to provide meaningfull reaction on this event.
 *
 * @section build_systems How to invoke qrsc from different build systems
 *
 * You can invoke @b qrsc manually each time your XML service description is
 * updated or new one added but it's better to do this from your build system
 * scrits. Here are some tips how to run @b qrsc from different buildsystems.
 *
 * @subsection scons
 *
 * You can find scons tool to invoke @b qrsc from scons in the
 * @e site_scons/site_tools/qrsc.py file of the library distribution. Just use
 * it in you project.
 *
 * @note This tool depends on qt4 tool which you can find it in this library
 * distribution or download from official project repository. See project home
 * page: http://www.iua.upf.edu/~dgarcia/Codders/sconstools.html
 *
 * This tool provides two builders
 * @li QRSService which creates services classes from XML service descritptions
 * and returns list of C++ sources files.
 * @li QRSClient which creates clients classes from XML service descritptions
 * and returns list of C++ sources files.
 *
 * Here is example how to use them in your SConstruct:
 * @code
 * env = Environment()
 * env.Tool('qt4')
 * env.Tool('qrs')
 *
 * env.EnableQt4Modules(['QtCore'])
 *
 * ServerSources=['server.cpp']
 * ServerSources += env.QRSService('service.xml')
 *
 * ClientSources=['client.cpp']
 * ClientSources += env.QRSClient('service.xml')
 *
 * env.Program('server',ServerSources)
 * env.Program('client',ClientSources)
 * @endcode
 *
 * @subsection qmake
 *
 * This version of QRemoteSignal library comes with qmake custom feature file.
 * You can find it in the library installation directory its name is
 * @b qremotesignal.prf . First of all you need to enshure that the directory
 * containig this file is searched by qmake for configuration features. The
 * simpliest way to do it is to add this directory path to the @b QMAKEFEATURES
 * envirunment variable. After that you can use this feature in you qmake
 * projects. Use @b QRS_SERVICE_INTERFACES variable in you project file to
 * specify which XML file should be used to generate servces classes. Use
 * @b QRS_CLIENT_INTERFACES variable to specify which XML files should be
 * used to generate client classes.
 *
 * Here is example of this feature ussage:
 * @li server.pro
 * @code
 * TEMPLATE = app
 * TARGET = server
 *
 * SOURCES = server.cpp
 * QRS_SERVICE_INTERFACES = service.xml
 *
 * CONFIG += qremotesignal
 * @endcode
 * @li client.pro
 * @code
 * TEMPLATE = app
 * TARGET = client
 *
 * SOURCES = client.cpp
 * QRS_CLIENT_INTERFACES = service.xml
 *
 * CONFIG += qremotesignal
 * @endcode
 */


/**
 * @file QRemoteSignal
 * @brief Public library header file containing all necessary classes
 *
 * Include this header file to automatically include all necessary internall
 * header files.
 */

/**
 * @namespace qrs
 * @brief Main library namespace
 */