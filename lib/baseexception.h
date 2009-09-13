/**
 * @file baseexception.h
 * @brief BaseException interface
 *
 * @author VestniK sir.vestnik@gmail.com
 * @date 18 Aug 2009
 */
#ifndef _BaseException_H
#define _BaseException_H

#include <exception>

#include <QtCore>

namespace qrs {

   /**
    * @brief Base class foe all project exceptions
    */
   class BaseException : public std::exception {
      public:
         BaseException(const QString& msg) {mReason = msg;};
         virtual ~BaseException() throw() {};

         /// Returns C string. Encoding is determined from locale
         virtual const char* what() throw() {
            return mReason.toLocal8Bit().constData();
         }
         virtual const QString& reason() const {return mReason;};
      private:
         QString mReason;
   };

}

#endif
