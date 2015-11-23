/**
 * @file absmessageserializer.h
 * @brief AbsMessageSerializer class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 15 Aug 2009
 */
#pragma once

#include <memory>

#include <QtCore/QObject>
#include <QtCore/QByteArray>

#include "qrsexport.h"
#include "message.h"
#include "serializationexceptions.h"

namespace qrs {

/**
 * @brief Abstrac tinterface for all remote call serializers.
 *
 * Serializer must provide two functions: serialize and deserialize. First
 * one converts instance of class qrs::Message (internal library message
 * representation) to a raw underlying protocol message. The second one
 * builds instance of qrs::Message from a raw protocol message. Instance
 * created by the deserialize function from raw messagege returned by the
 * serialize function should be equal to the initial instance.
 *
 * When implementing this two function keep thread safety in mind. In this
 * case you can use one single global instance of your serializer in all
 * threads. By default all ServicesMessages use the same serializer
 * instance. If you have implemented serializer which is not thread safe
 * and want to use it in multythreaded application you should follow some
 * rules in order to have no thread-safety issues:
 * @li Use different ServicesManager instances in different threads.
 * @li Do not set non-thread-safe serializer as default with
 * ServicesManager::setDefaultSerializer() function.
 * @li Ensure that serializers from different threads use different
 * instances of non-thread-safe serializer.
 *
 * There is a simple template class which helps to create and manage single
 * global instance of serializer: qrs::GlobalSerializer. Serializers which
 * comes with the library itself uses this class to store global instace.
 * It's done with macro like:
 * @code
 * #define jsonSerializer qrs::GlobalSerializer<qrs::JsonSerializer>::instance()
 * @endcode
 * Common rule is name of macro is the same as class name but the first
 * letter is lowercase. You can use the same approach when implementing
 * your own serializers.
 *
 * If you serializer supports several version of the underlying RPC
 * protocol you can pass it as a second template parameter of the
 * GlobalSerializer class:
 * @code
 * #define qDataStreamSerializer_4_5 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_5>::instance()
 * @endcode
 *
 * Once you've created your own serializer you can test it to compatibility
 * with this library using serializers test suit. You need to take 4 files
 * from the tests/serializers directory of the sources package of
 * QRemoteSignal library:
 * @li messagetesttools.h
 * @li messagetesttools.cpp
 * @li serializerstestsuit.h
 * @li serializerstestsuit.cpp
 *
 * Then you need to create instance of @b SerializersTestSuit class passing
 * to its constructor instance of you serializer class and run tests using
 *  @b QTest::qExec function. You can also use @b addDeserializationErrorTestCase
 * method of the @b SerializersTestSuit class to test that your serializer
 * throws MessageParsingException on attempt to deserialize some specific
 * raw messages.
 *
 * Here is example of main function for tests of the JsonSerializer class
 * which comes with this library:
 * @include serializers/json.cpp
 */
class QRS_EXPORT AbsMessageSerializer: public QObject {
public:
    /**
     * This constructor creates new instance with given parent.
     * mVersion constant is set to 0.
     */
    explicit AbsMessageSerializer(QObject* parent = 0):
        QObject(parent),
        mVersion(0) {};
    /**
     * This constructor creates new instance with given parent.
     * mVersion constant is set to version parameter value.
     *
     * @sa mVersion
     */
    explicit AbsMessageSerializer(int version, QObject* parent = 0):
        QObject(parent),
        mVersion(version) {};
    virtual ~AbsMessageSerializer() {};

    /**
     * @return version of the protocol used by this serializer
     * instance.
     */
    int version() const {return mVersion;}

    /**
     * @brief Serealize Message
     *
     * @throw UnsupportedTypeException if remote call object contain data
     * which can't be converted to the underlying protocol message. For
     * example Message::params contain parameters of types not supported
     * by underlying protocol.
     *
     * @param msg Message class instance to be converted to a underlying
     * protocol message.
     *
     * @return raw underlying protocol message.
     *
     * @sa deserialize
     */
    virtual QByteArray serialize(const Message& msg)
        throw(UnsupportedTypeException) = 0;
    /**
     * @brief Deserealize Message
     *
     * @throw MessageParsingException in case of error during message
     * parsing
     *
     * @param msg underlying protocol raw message to be converted to a
     * Message class instance
     *
     * @return Message class instance
     *
     * @sa serialize
     */
    virtual MessageAP deserialize(const QByteArray& msg)
        throw(MessageParsingException) = 0;

private:
    /**
     * @brief Serializer version.
     *
     * This property allows you to store version of your serializer
     * class. I assume that newer version of a serializer class have
     * greater value of this property while if it's set to 0 the latest
     * version is used. It's better to follow this numeration schema if
     * you are going to use GlobalSerializer template class.
     */
    const int mVersion;
};

}
