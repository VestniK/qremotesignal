/**
 * @file jsonserializer.h
 * @brief JsonSerializer interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Sep 2009
 */
#ifndef qrsjsonserializer_h
#define qrsjsonserializer_h

#include "absremotecallserializer.h"

namespace qrs {

   class JsonSerializer: public AbsRemoteCallSerializer {
      public:
         JsonSerializer (QObject *parent=0):AbsRemoteCallSerializer(parent) {};
         virtual ~JsonSerializer() {};

         virtual QByteArray serialize ( const RemoteCall& rc )
               throw(UnsupportedTypeException);
         virtual RemoteCallAP deserialize ( const QByteArray& msg )
               throw(MessageParsingException,ErrorMessageException);
   };

}

#endif
