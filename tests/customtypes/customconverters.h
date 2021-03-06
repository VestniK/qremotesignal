/**
 * @file customconverters.h
 * @brief Conertors for custom types definition
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 16 Sep 2009
 */
#ifndef _CustomConverters_H
#define _CustomConverters_H

#include <QtCore/QVariant>

#include "customstruct.h"

namespace qrs {

    QVariant createArg(const CustomStruct& val);
    bool getArgValue(const QVariant& arg, CustomStruct& res);

    QVariant createArg(const ListStruct& val);
    bool getArgValue(const QVariant& arg, ListStruct& res);

}

#endif
