/**
 * @file qdatastreamserializer.cpp
 * @brief QDataStreamSerializer implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 27 Jan 2010
 */
#include "qdatastreamserializer.h"

#include <QtCore/QBuffer>

using namespace qrs;

QDataStream &operator<<(QDataStream &stream, const Message &msg) {
    qint8 type,errorType;
    type = (qint8)msg.type();
    errorType = (qint8)msg.errorType();
    stream << type << errorType;
    stream << msg.error();
    stream << msg.service() << msg.method();
    stream << msg.params();
    return stream;
}

QDataStream &operator>>(QDataStream &stream, Message &msg) {
    qint8 type,errorType;
    QString error,service,method;
    QVariantMap params;
    stream >> type;
    if ( stream.status() != QDataStream::Ok ) return stream;
    stream >> errorType;
    if ( stream.status() != QDataStream::Ok ) return stream;
    stream >> error;
    if ( stream.status() != QDataStream::Ok ) return stream;
    stream >> service;
    if ( stream.status() != QDataStream::Ok ) return stream;
    stream >> method;
    if ( stream.status() != QDataStream::Ok ) return stream;
    stream >> params;
    if ( stream.status() != QDataStream::Ok ) return stream;
    msg.setType((Message::MsgType)type);
    msg.setErrorType((Message::ErrorType)errorType);
    msg.setError(error);
    msg.setService(service);
    msg.setMethod(method);
    msg.setParams(params);
    return stream;
}

MessageAP QDataStreamSerializer::deserialize(const QByteArray& msg)
        throw(MessageParsingException) {
    QBuffer dev;
    dev.setData(msg);
    dev.open(QIODevice::ReadOnly);
    QDataStream stream(&dev);
    if ( version() != 0 ) stream.setVersion( version() );
    Message *message = new Message;
    stream >> *message;
    if ( stream.status() != QDataStream::Ok ) {
        QString desc;
        switch( stream.status() ) {
            case QDataStream::ReadPastEnd :
                desc = "Message incompleate";
                break;
            case QDataStream::ReadCorruptData :
                desc = "Message corrupted";
                break;
            default: break;
        }
        MessageParsingException err(desc,Message::ProtocolError);
        throw(err);
    }
    return MessageAP(message);
}

QByteArray QDataStreamSerializer::serialize( const Message& msg )
        throw(UnsupportedTypeException) {
    QBuffer dev;
    dev.open(QIODevice::WriteOnly);
    QDataStream stream(&dev);
    if ( version() != 0 ) stream.setVersion( version() );
    stream << msg;
    return dev.data();
}
