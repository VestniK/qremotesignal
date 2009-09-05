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
   void appendArg(Message& msg, const QString& name, int val) {
      msg.params().insert(name,QVariant(val));
   }

   bool getArgValue(const Message& msg,const QString& name, int& res) {
      if ( !msg.params().contains(name) ) {
         return false;
      }
      if ( !msg.params()[name].canConvert<int>() ) {
         return false;
      }
      res = msg.params()[name].value<int>();
      return true;
   }
   // string
   void appendArg(Message& msg, const QString& name, const QString& val) {
      msg.params().insert(name,QVariant(val));
   }

   bool getArgValue(const Message& msg,const QString& name, QString& res) {
      if ( !msg.params().contains(name) ) {
         return false;
      }
      if ( !msg.params()[name].canConvert<QString>() ) {
         return false;
      }
      res = msg.params()[name].value<QString>();
      return true;
   }

}
