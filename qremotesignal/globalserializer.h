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
    * derived from AbsMessageSerializer given as a template parameter and
    * manage this instance cleanup at the end of application execution. This
    * class doesn't designed to be thread safe. If you are going to use it in
    * multythread environment ensure that object managed by this class is
    * designed to be thread safe.
    */
   template<class T>
   class GlobalSerializer {
      public:
         static AbsMessageSerializer* instance() {
            QMutexLocker locker(&mMutex);
            if ( mInstance.get() == 0 ) {
               mInstance.reset ( new T() );
            }
            return mInstance.get();
         }
      private:
         static std::auto_ptr<T> mInstance;
         static QMutex mMutex;
   };

   template<class T>
   std::auto_ptr<T> GlobalSerializer<T>::mInstance;

   template<class T>
   QMutex GlobalSerializer<T>::mMutex;

}

#endif
