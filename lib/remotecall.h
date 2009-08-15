/**
 * @file remotecall.h
 * @brief RemoteCall class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _RemoteCall_H
#define _RemoteCall_H

#include <QtCore>

namespace qrs {

   class RemoteCall {
      public:
         RemoteCall() {};
         ~RemoteCall() {};

         void setService ( const QString& val ) {service = val;};
         const QString& getService() const {return service;};

         void setUri ( const QString& val ) {uri = val;};
         const QString& getUri() const {return uri;};

         void setMethod ( const QString& val ) {method = val;};
         const QString& getMethod() const {return method;}

         const QMap<QString,QVariant>* params() const {return paramsMap;};
         QMap<QString,QVariant>* params() {return paramsMap;};

      private:
         QString service;
         QString uri;
         QString method;
         QMap<QString,QVariant> paramsMap;
   };

}

#endif
