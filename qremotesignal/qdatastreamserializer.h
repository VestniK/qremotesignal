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

    template<int protocolVersion = 0>
    class QRS_EXPORT QDataStreamSerializer : public AbsMessageSerializer {
        public:
            explicit QDataStreamSerializer(QObject *parent = 0):AbsMessageSerializer(parent) {}
            virtual ~QDataStreamSerializer() {}

            virtual MessageAP deserialize( const QByteArray& msg ) throw(MessageParsingException) {
                QBuffer dev;
                dev.setData(msg);
                dev.open(QIODevice::ReadOnly);
                QDataStream stream(&dev);
                stream.setVersion(protocolVersion);
                Message *message = new Message;
                stream >> *message;
                return MessageAP(message);
            }
            virtual QByteArray serialize( const Message& msg ) throw(UnsupportedTypeException) {
                QBuffer dev;
                dev.open(QIODevice::WriteOnly);
                QDataStream stream(&dev);
                stream.setVersion(protocolVersion);
                stream << msg;
                return dev.data();
            }
    };

}

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 1.0 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_1_0 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_1_0> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 2.0 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_2_0 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_2_0> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 2.1 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_2_1 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_2_1> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 3.0 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_3_0 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_3_0> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 3.1 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_3_1 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_3_1> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 3.3 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_3_3 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_3_3> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.0 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_0 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_4_0> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.1 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_1 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_4_1> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.2 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_2 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_4_2> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.3 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_3 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_4_3> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.4 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_4 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_4_4> >::instance()

/**
 * Pointer to single global instance of QDataStreamSerializer class which uses
 * Qt 4.5 version of the QDataStream protocol.
 */
#define qDataStreamSerializer_4_5 qrs::GlobalSerializer< qrs::QDataStreamSerializer<QDataStream::Qt_4_5> >::instance()

#endif // QDATASTREAMSERIALIZER_H
