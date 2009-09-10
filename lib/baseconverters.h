/**
 * @file baseconverters.h
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _BaseConverters_H
#define _BaseConverters_H

#include "message.h"

namespace qrs {

   QVariant createArg(int val);
   bool getArgValue(const QVariant& arg, int& res);

   QVariant createArg(const QString& val);
   bool getArgValue(const QVariant& arg, QString& res);

}

#endif
