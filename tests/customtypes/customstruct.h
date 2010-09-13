/**
 * @file customstruct.h
 * @brief CustomStruct structure declaration
 *
 * CustomStruct is a structure created to test QRemoteSignal
 * library custom types support.
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 16 Sep 2009
 */
#ifndef _CustomStruct_H
#define _CustomStruct_H

#include <QtCore/QtGlobal>
#include <QtCore/QString>
#include <QtCore/QList>

struct CustomStruct {
   qint32 mInt;
   QString mString;
};

Q_DECLARE_METATYPE(CustomStruct);

struct ListStruct
{
    QString name;
    QList<quint16> list;
};

#endif
