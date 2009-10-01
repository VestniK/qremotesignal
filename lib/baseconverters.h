/**
 * @file baseconverters.h
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _BaseConverters_H
#define _BaseConverters_H

#include <QtCore>

#include "message.h"

namespace qrs {

   // ----- unsigned long long -----
   QVariant createArg(unsigned long long val);
   bool getArgValue(const QVariant& arg, unsigned long long& res);

   // ----- unsigned long -----
   QVariant createArg(unsigned long val);
   bool getArgValue(const QVariant& arg, unsigned long& res);

   // ----- unsigned -----
   QVariant createArg(unsigned val);
   bool getArgValue(const QVariant& arg, unsigned& res);

   // ----- unsigned short -----
   QVariant createArg(unsigned short val);
   bool getArgValue(const QVariant& arg, unsigned short& res);

   // ----- unsigned char -----
   QVariant createArg(unsigned char val);
   bool getArgValue(const QVariant& arg, unsigned char& res);

   // ----- long long -----
   QVariant createArg(long long val);
   bool getArgValue(const QVariant& arg, long long& res);

   // ----- long -----
   QVariant createArg(long val);
   bool getArgValue(const QVariant& arg, long& res);

   // ----- int -----
   QVariant createArg(int val);
   bool getArgValue(const QVariant& arg, int& res);

   // ----- short -----
   QVariant createArg(short val);
   bool getArgValue(const QVariant& arg, short& res);

   // ----- signed char -----
   QVariant createArg(signed char val);
   bool getArgValue(const QVariant& arg, signed char& res);

   // ----- char -----
   QVariant createArg(char val);
   bool getArgValue(const QVariant& arg, char& res);

   // ----- QChar -----
   QVariant createArg(QChar val);
   bool getArgValue(const QVariant& arg, QChar& res);

   // ----- QString -----
   QVariant createArg(const QString& val);
   bool getArgValue(const QVariant& arg, QString& res);

   // ----- QList -----
   template<typename T>
   QVariant createArg(const QList<T>& val) {
      QVariantList res;
      foreach(T t, val) {
         res.append( createArg(t) );
      }
      return QVariant(res);
   }

   template<typename T>
   bool getArgValue(const QVariant& arg, QList<T>& res) {
      if( !arg.canConvert<QVariantList>() ){
         return false;
      }
      QVariantList argContent = arg.toList();
      res.clear();
      foreach(QVariant item, argContent) {
         T t;
         if ( ! getArgValue(item, t) ) {
            return false;
         }
         res.append(t);
      }
      return true;
   }

   // ----- QMap -----
   template<typename T>
   QVariant createArg(const QMap<QString,T>& val) {
      QVariantMap res;
      typename QMap<QString,T>::const_iterator indx = val.begin();
      while ( indx != val.end() ) {
         res[indx.key()] = createArg(indx.value());
         indx++;
      }
      return QVariant(res);
   }

   template<typename T>
   bool getArgValue(const QVariant& arg, QMap<QString,T>& res) {
      if( !arg.canConvert<QVariantMap>() ){
         return false;
      }
      QVariantMap argContent = arg.toMap();
      res.clear();
      QVariantMap::const_iterator indx = argContent.begin();
      while ( indx != argContent.end() ) {
         T t;
         if ( !getArgValue(indx.value() , t) ) {
            return false;
         }
         res[indx.key()] = t;
         indx++;
      }
      return true;
   }
}

#endif
