/**
 * @file baseconverters.cpp
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "baseconverters.h"

#include <QtSoapSimpleType>

namespace QRemoteSignal {
   // int
   QtSoapType* createArg(const QString name, int val) {
      return new QtSoapSimpleType(QtSoapQName(name,""), val);
   }

   bool getArgValue(const QtSoapType& arg, int& res) {
      if ( !arg.isValid() ) {
         return false;
      }
      if ( !arg.value().canConvert<int>() ) {
         return false;
      }
      res = arg.value().value<int>();
      return true;
   }
   // string
   QtSoapType* createArg(const QString name, const QString& val) {
      return new QtSoapSimpleType(QtSoapQName(name,""), val);
   }

   bool getArgValue(const QtSoapType& arg, QString& res) {
      if ( !arg.isValid() ) {
         return false;
      }
      if ( !arg.value().canConvert<QString>() ) {
         return false;
      }
      res = arg.value().value<QString>();
      return true;
   }

}
