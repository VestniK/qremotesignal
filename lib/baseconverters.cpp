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
   QVariant createArg(int val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, int& res) {
      if ( !arg.canConvert<int>() ) {
         return false;
      }
      bool convRes = false;
      res = arg.toInt(&convRes);
      return convRes;
   }
   // string
   QVariant createArg(const QString& val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, QString& res) {
      if ( !arg.canConvert<QString>() ) {
         return false;
      }
      res = arg.toString();
      return true;
   }

}
