/**
 * @file baseconverters.h
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _BaseConverters_H
#define _BaseConverters_H

#include <QtSoapType>

namespace qrs {

   QtSoapType* createArg(const QString name, int val);
   bool getArgValue(const QtSoapType& arg, int& res);

   QtSoapType* createArg(const QString name, const QString& val);
   bool getArgValue(const QtSoapType& arg, QString& res);

   // Lists,vectors and other stuff

   template<class T>
   QtSoapType* createArg(const QString& name, const QList<T>& val) {
      QtSoapArray* res = new QtSoapArray(QtSoapQName(name,""));
      for(int i = 0; i<val.size(); i++) {
         res->append(createArg(QString::number(i),val[i]));
      }
      return res;
   }

   template<class T>
   bool getArgValue(const QtSoapType& arg, QList<T>& res) {
      if ( ! arg.isValid() ) {
         return false;
      }
      const QtSoapArray *array = dynamic_cast<const QtSoapArray*>( &arg );
      if ( array == 0 ) {
         return false;
      }
      res.clear();
      for (int i=0; i<array->count(); i++) {
         T t;
         if ( !getArgValue(array->at(i), t) ) {
            return false;
         }
         res.append(t);
      }
      return true;
   }

   template<class T>
   QtSoapType* createArg(const QString& name, const QVector<T>& val) {
      QtSoapArray* res = new QtSoapArray(QtSoapQName(name,""));
      for(int i = 0; i<val.size(); i++) {
         res->append(createArg(QString::number(i),val[i]));
      }
      return res;
   }

   template<class T>
   bool getArgValue(const QtSoapType& arg, QVector<T>& res) {
      if ( ! arg.isValid() ) {
         return false;
      }
      const QtSoapArray *array = dynamic_cast<const QtSoapArray*>( &arg );
      if ( array == 0 ) {
         return false;
      }
      res.clear();
      for (int i=0; i<array->count(); i++) {
         T t;
         if ( !getArgValue(array->at(i), t) ) {
            return false;
         }
         res.append(t);
      }
      return true;
   }

}

#endif
