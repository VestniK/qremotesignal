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

class AbsService : public QObject {
   public:
      AbsService(QObject *parent = 0): QObject(parent) {};
      virtual ~AbsService() {};

      virtual void processMessage(const QtSoapType& method)
            throw(IncorrectMethodException) = 0;
      virtual const QString& getUri() const = 0;
};

#endif
