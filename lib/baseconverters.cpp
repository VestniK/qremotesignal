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
      /* According to Qt 4.5 documentation QVariant::toInt(bool* ok) doesn't
      set *ok to false in case of numeric values out of int range while
      QString::toInt does. That's why I use such strange way to obtain the
      value. */
      res = arg.toString().toInt(&convRes,0);
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
