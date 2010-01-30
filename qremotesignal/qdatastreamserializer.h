/**
 * @file qdatastreamserializer.h
 * @brief QDataStreamSerializer implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 27 Jan 2010
 */
#ifndef QDATASTREAMSERIALIZER_H
#define QDATASTREAMSERIALIZER_H

#include <QtCore/QDataStream>

#include "qrsexport.h"
#include "absmessageserializer.h"
#include "globalserializer.h"

QDataStream &operator<<(QDataStream &stream, const qrs::Message &msg);
QDataStream &operator>>(QDataStream &stream, qrs::Message &msg);

namespace qrs {

    /**
     * @brief Serializer based on QDataStream standard Qt class
     * 
     * This class serializes internal library remote call representation into
     * a binary message using Qt4 QDataStream class. serialize and deserialize
     * funtions are reentrant and thus you can use single instance of this
     * class in different threads.
     * 
     * Order and format of serialization of qrs::Message class is the
     * following:
     *   -# Message type as @b qint8 number.
     *   -# Error type as @b qint8 number.
     *   -# Error string (even if empty) as @b QString.
     *   -# Service name as @b QString.
     *   -# Method name as @b QString.
     *   -# Renote call parameters as @b QVariantMap.
     * 
     * You can create and manage instances of this class manually but it's more
     * convivient to use predefined macroses which allows you to have one
     * global instance of this class.
     * 
     * @note QDataStream protocol version older then QDataStream::Qt_3_3 can't
     * pass tests from the serializers test suit. Ussage of such versions is
     * depricated.
     * 
     * @sa qDataStreamSerializer_3_3
     * @sa qDataStreamSerializer_4_0
     * @sa qDataStreamSerializer_4_1
     * @sa qDataStreamSerializer_4_2
     * @sa qDataStreamSerializer_4_3
     * @sa qDataStreamSerializer_4_4
     * @sa qDataStreamSerializer_4_5
     * @sa qDataStreamSerializer
     */
    class QRS_EXPORT QDataStreamSerializer : public AbsMessageSerializer {
        public:
            explicit QDataStreamSerializer(QObject *parent = 0):
                AbsMessageSerializer(parent) {}
            explicit QDataStreamSerializer(int version, QObject *parent = 0):
                AbsMessageSerializer(version,parent) {}
            virtual ~QDataStreamSerializer() {}

            /// @copydoc AbsMessageSerializer::deserialize
            virtual MessageAP deserialize(const QByteArray& msg) 
                throw(MessageParsingException);

            /// @copydoc AbsMessageSerializer::serialize
            virtual QByteArray serialize( const Message& msg )
                throw(UnsupportedTypeException);
                
        private:
            Q_DISABLE_COPY(QDataStreamSerializer);
    };

}

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 3.3 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_3_3 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_3_3>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.0 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_0 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_0>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.1 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_1 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_1>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.2 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_2 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_2>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.3 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_3 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_3>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.4 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_4 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_4>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.5 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_5 qrs::GlobalSerializer<qrs::QDataStreamSerializer,QDataStream::Qt_4_5>::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * latest version of the QDataStream protocol available in Qt library used to
 * build this library.
 * 
 * In general it's not recommended to use this macro since th version of the
 * underlying protocol used by serializer is depends on environment at build
 * time and may be unpredictable.
 */
#define qDataStreamSerializer qrs::GlobalSerializer<qrs::QDataStreamSerializer>::instance()

#endif // QDATASTREAMSERIALIZER_H
