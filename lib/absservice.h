/**
 * @file absservice.h
 * @brief AbsService class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _AbsService_H
#define _AbsService_H

#include <exception>

#include <QtCore>
#include <QtSoapType>

namespace qrs {

   /**
    * @brief Exception to be thrown on attempt to call unknown method
    */
   class IncorrectMethodException: public std::exception {
      public:
         virtual const char* what() const throw() {
            return error.toLocal8Bit().constData();
         };

         IncorrectMethodException(const QString& msg) {error = msg;};
         virtual ~IncorrectMethodException() throw() {};
         const QString& getError() const {return error;};
      private:
         QString error;
   };

   /**
    * @brief Abstract interface for a service classes
    *
    * You shouldn't implement real services classes by yourself. Describe
    * service interface in XML document and use XML interface compiler
    * tool (xic) to generate service and client classes.
    */
   class AbsService : public QObject {
      public:
         AbsService(QObject *parent = 0): QObject(parent) {};
         virtual ~AbsService() {};

         virtual void processMessage(const QtSoapType& method)
               throw(IncorrectMethodException) = 0;
         virtual const QString& getUri() const = 0;
   };

}

#endif
