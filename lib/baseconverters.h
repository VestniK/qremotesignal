/**
 * @file baseconverters.h
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _BaseConverters_H
#define _BaseConverters_H

#include "remotecall.h"

namespace qrs {

   void appendArg(RemoteCall& rc, const QString& name, int val);
   bool getArgValue(const RemoteCall& rc,const QString& name, int& res);

   void appendArg(RemoteCall& rc, const QString& name, const QString& val);
   bool getArgValue(const RemoteCall& rc,const QString& name, QString& res);

}

#endif
