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
    * @brief Base class for all project exception classes
    *
    * @internal
    * Library public interface methods doesn't throws exceptions outside.
    * Exceptions are used only internally. You don't have to warry about
    * catching exceptions of this or derived from this classes.
    */
   class BaseException : public std::exception {
      public:
         /**
          * @brief Creates new instance of exception with given error description.
          *
          * @param msg human readable error description.
          */
         BaseException(const QString& msg) {mReason = msg;};
         virtual ~BaseException() throw() {};

         /**
          * @brief Human readable error description
          *
          * @returns C string. Encoding is determined from locale
          */
         virtual const char* what() const throw() {
            return mReason.toLocal8Bit().constData();
         }
         /// @returns human readable error description
         virtual const QString& reason() const {return mReason;};
      private:
         QString mReason;
   };

}

#endif
