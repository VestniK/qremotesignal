/**
 * @file customconverters.cpp
 * @brief Conertors for custom types implementation
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 16 Sep 2009
 */
#include "customconverters.h"

#include <QRemoteSignal>

// The next header requirement shows that API backward compatibility is
// broken in the version 1.2.0.
#include <templateconverters.h>

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

   QVariant createArg(const ListStruct &val)
   {
       QVariantMap res;
       res["name"] = QVariant(val.name);
       res["list"] = createArg(val.list);
       return QVariant(res);
   }

   bool getArgValue(const QVariant& arg, ListStruct& res)
   {
       QVariantMap argMap = arg.toMap();
       if ( argMap.isEmpty() ) {
           return false;
       }
       if ( argMap.contains("name") && argMap.contains("list") ) {
           if ( !getArgValue( argMap["name"], res.name ) ) {
               return false;
           }
           if ( !getArgValue( argMap["list"], res.list ) ) {
               return false;
           }
       } else {
           return false;
       }
       return true;
   }

}
