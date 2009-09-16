/**
 * @file customconvertors.cpp
 * @brief Conertors for custom types implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 16 Sep 2009
 */
#include "customconvertors.h"

#include <QRemoteSignal>

namespace qrs {

   QVariant createArg(const CustomStruct& val) {
      QVariantMap res;
      res["mInt"] = QVariant(val.mInt);
      res["mString"] = QVariant(val.mString);
      return QVariant(res);
   }

   bool getArgValue(const QVariant& arg, CustomStruct& res) {
      QVariantMap argMap = arg.toMap();
      if ( argMap.isEmpty() ) {
         return false;
      }
      if ( argMap.contains("mInt") && argMap.contains("mString") ) {
         if ( !getArgValue( argMap["mInt"], res.mInt ) ) {
            return false;
         }
         if ( !getArgValue( argMap["mString"], res.mString ) ) {
            return false;
         }
      } else {
         return false;
      }
      return true;
   }

}
