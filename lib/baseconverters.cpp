/**
 * @file baseconverters.cpp
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "baseconverters.h"

namespace qrs {
   // int
   void appendArg(RemoteCall& rc, const QString& name, int val) {
      rc.params().insert(name,QVariant(val));
   }

   bool getArgValue(const RemoteCall& rc,const QString& name, int& res) {
      if ( !rc.params().contains(name) ) {
         return false;
      }
      if ( !rc.params()[name].canConvert<int>() ) {
         return false;
      }
      res = rc.params()[name].value<int>();
      return true;
   }
   // string
   void appendArg(RemoteCall& rc, const QString& name, const QString& val) {
      rc.params().insert(name,QVariant(val));
   }

   bool getArgValue(const RemoteCall& rc,const QString& name, QString& res) {
      if ( !rc.params().contains(name) ) {
         return false;
      }
      if ( !rc.params()[name].canConvert<QString>() ) {
         return false;
      }
      res = rc.params()[name].value<QString>();
      return true;
   }

}
