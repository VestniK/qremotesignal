/**
 * @file soapserializer.h
 * @brief SoapSerializer class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 18 Aug 2009
 */
#ifndef _SoapSerializer_H
#define _SoapSerializer_H

#include <QtCore>

#include "absremotecallserializer.h"
#include "remotecall.h"

class QtSoapType;

namespace qrs {

   /**
    * @brief SOAP serializer
    * @sa AbsRemoteCallSerializer
    */
   class SoapSerializer : public AbsRemoteCallSerializer {
      public:
         SoapSerializer(QObject parent = 0):AbsRemoteCallSerializer(parent) {};
         virtual ~SoapSerializer() {};

         virtual QString serialize ( const RemoteCall& rc )
               throw(IncorrectTypeException);
         virtual RemoteCall deserialize ( const QString& rc )
               throw(MessageParsingException,ErrorMessageException);

      private:
         QtSoapType* createArg(const QString& name, const QVariant value);
   };

}

#endif
