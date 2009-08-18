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
         BaseException(const QString& msg) {reason = msg;};
         virtual ~BaseException() throw() {};

         /// Returns C string encoding determined from locale
         virtual const char* what() throw() {
            return reason.toLocal8Bit().constData();
         }
         const QString& getReason() {return reason;};
      private:
         QString reason;
   };

}

#endif
