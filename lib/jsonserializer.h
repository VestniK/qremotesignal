/**
 * @file jsonserializer.h
 * @brief JsonSerializer interface
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Sep 2009
 */
#ifndef qrsjsonserializer_h
#define qrsjsonserializer_h

#include "absmessageserializer.h"

namespace qrs {

   class JsonSerializer: public AbsMessageSerializer {
      public:
         JsonSerializer (QObject *parent=0):AbsMessageSerializer(parent) {};
         virtual ~JsonSerializer() {};

         virtual QByteArray serialize ( const Message& msg )
               throw(UnsupportedTypeException);
         virtual MessageAP deserialize ( const QByteArray& msg )
               throw(MessageParsingException);
   };

}

#endif
