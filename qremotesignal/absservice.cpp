/**
 * @file absservice.cpp
 * @brief AbsService class methods definitions
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 09 May 2010
 */
#include "absservice.h"
#include <QtCore/QtGlobal>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaMethod>
#include <QtCore/QByteArray>

#if (QT_VERSION >= QT_VERSION_CHECK(5,2,0))
#    define QT_METHOD_SIGNATURE(method) method.methodSignature().constData()
#else
#    define QT_METHOD_SIGNATURE(method) method.signature()
#endif

using namespace qrs;

bool AbsService::autoconnect(QObject *target) {
    const QMetaObject *serviceMetaObject = this->metaObject();
    const QMetaObject *targetMetaObject = target->metaObject();
    bool res = true;
    for ( int i = serviceMetaObject->methodOffset();
          i < serviceMetaObject->methodCount();
          i++ ) 
    {
        QMetaMethod method = serviceMetaObject->method(i);

        QByteArray nsignature = QMetaObject::normalizedSignature(QT_METHOD_SIGNATURE(method));

        if ( method.methodType() == QMetaMethod::Signal )
        {
            int pairIndx = targetMetaObject->indexOfSlot(nsignature);
            if (pairIndx == -1) 
            {
                res = false;
                qWarning("qrs::AbsService::autoconnect: failed to find pair for the signal %s::%s",
                         serviceMetaObject->className(), QT_METHOD_SIGNATURE(method));
                continue;
            }
            QMetaMethod pair = targetMetaObject->method(pairIndx);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
            if (!connect(this,method,target,pair)) 
            {
                res = false;
                qWarning("qrs::AbsService::autoconnect: failed to connect %s::%s to %s::%s",
                         serviceMetaObject->className(), QT_METHOD_SIGNATURE(method),
                         targetMetaObject->className(), QT_METHOD_SIGNATURE(pair));
                continue;
            }
#else
            // Some kluges which relies on Qt4 SIGNAL and SLOT macro implementation
            QByteArray signal;
            signal.reserve(qstrlen(method.signature())+1);
            signal.append((char)(QSIGNAL_CODE + '0'));
            signal.append(method.signature());

            QByteArray slot;
            slot.reserve(qstrlen(pair.signature())+1);
            slot.append((char)(QSLOT_CODE + '0'));
            slot.append(pair.signature());

            if (!connect(this,signal.constData(), target,slot.constData())) {
                res = false;
                qWarning("qrs::AbsService::autoconnect: failed to connect %s::%s to %s::%s",
                         serviceMetaObject->className(), QT_METHOD_SIGNATURE(method),
                         targetMetaObject->className(), QT_METHOD_SIGNATURE(pair));
                continue;
            }
#endif
        } else if ( method.methodType() == QMetaMethod::Slot ) {
            int pairIndx = targetMetaObject->indexOfSignal(nsignature);
            if (pairIndx == -1) {
                res = false;
                qWarning("qrs::AbsService::autoconnect: failed to find pair for the slot %s::%s",
                         serviceMetaObject->className(), QT_METHOD_SIGNATURE(method));
                continue;
            }
            QMetaMethod pair = targetMetaObject->method(pairIndx);
#if (QT_VERSION >= QT_VERSION_CHECK(4,8,0))
            if (!connect(target,pair,this,method)){
                res = false;
                qWarning("qrs::AbsService::autoconnect: failed to connect %s::%s to %s::%s",
                         targetMetaObject->className(), QT_METHOD_SIGNATURE(pair),
                         serviceMetaObject->className(), QT_METHOD_SIGNATURE(method));
                continue;
            }
#else
            // Some kluges which relies on Qt4 SIGNAL and SLOT macro implementation
            QByteArray signal;
            signal.reserve(qstrlen(pair.signature())+1);
            signal.append((char)(QSIGNAL_CODE + '0'));
            signal.append(pair.signature());

            QByteArray slot;
            slot.reserve(qstrlen(method.signature())+1);
            slot.append((char)(QSLOT_CODE + '0'));
            slot.append(method.signature());

            if (!connect(target,signal.constData(), this,slot.constData())) {
                res = false;
                qWarning("qrs::AbsService::autoconnect: failed to connect %s::%s to %s::%s",
                         targetMetaObject->className(), QT_METHOD_SIGNATURE(pair),
                         serviceMetaObject->className(), QT_METHOD_SIGNATURE(method));
                continue;
            }
#endif
        } else {
            // Nothing to do with other types of methods
            continue;
        }
    }
    return res;
}
