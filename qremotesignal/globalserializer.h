/**
* @file globalserializer.h
* @brief GlobalSerializer template class declaration
*
* @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
* @date 26 Dec 2009
*/
#ifndef _SingleGlobal_H
#define _SingleGlobal_H

#include <memory>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "absmessageserializer.h"

namespace qrs {

   /**
    * @brief Singleton factory manages one instance of serializer.
    *
    * Simple template class which creates one globall instance of the type
    * derived from AbsMessageSerializer given as a first template parameter and
    * manage this instance cleanup at the end of application execution. This
    * class designed to be thread safe however serializer instance wrapped by
    * it may by not. If you are going to use it in multythread environment
    * ensure that object managed by this class is designed to be thread safe.
    * 
    * Second template parameter allows you to decide which version of a
    * serializer to use.
    */
   template<class T, int protocolVersion = 0>
   class GlobalSerializer {
      public:
         static AbsMessageSerializer* instance() {
            QMutexLocker locker(&mMutex);
            if ( mInstance.get() == 0 ) {
               mInstance.reset ( new T(protocolVersion) );
            }
            return mInstance.get();
         }
      private:
         static std::auto_ptr<T> mInstance;
         static QMutex mMutex;
   };

   template<class T, int protocolVersion>
   std::auto_ptr<T> GlobalSerializer<T,protocolVersion>::mInstance;

   template<class T, int protocolVersion>
   QMutex GlobalSerializer<T,protocolVersion>::mMutex;

}

#endif
