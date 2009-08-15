/**
 * @file absremotecallserializer.h
 * @brief AbsRemoteCallSerializer class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 15 Jul 2009
 */
#ifndef _AbsRemoteCallSerializer_H
#define _AbsRemoteCallSerializer_H

#include "remotecall.h"

namespace qrs {

   /**
    * @brief Abstrac tinterface for all remote call serializers.
    *
    * Serializer must provide two functions: serialize and deserialize. Those
    * functions should be inverse for each other. So the following statement
    * should be true: rc == deserialize(serialize(rc))
    */
   class AbsRemoteCallSerializer {
      public:
         AbsRemoteCallSerializer() {};
         virtual ~AbsRemoteCallSerializer() = 0;

         /**
          * @brief Serealize RemoteCall
          *
          * @sa deserialize
          *
          * @param rc RemoteCall class instance to be converted to a string
          * @return string representation of a remote call (SOAP, XML-RPC,
          * JSON ...)
          */
         virtual QString serialize(const RemoteCall& rc) = 0;
         /**
          * @brief Serealize RemoteCall
          *
          * @sa serialize
          *
          * @param rc remote call string representation (SOAP, XML-RPC, JSON)
          * @return RemoteCall class instance
          */
         virtual RemoteCall deserialize(const QString& rc) = 0;
   };

}

#endif
