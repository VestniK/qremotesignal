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

#include "qrsexport.h"
#include "message.h"

namespace qrs {

   // ----- unsigned long long -----
   QRS_EXPORT QVariant createArg(unsigned long long val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, unsigned long long& res);

   // ----- unsigned long -----
   QRS_EXPORT QVariant createArg(unsigned long val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, unsigned long& res);

   // ----- unsigned -----
   QRS_EXPORT QVariant createArg(unsigned val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, unsigned& res);

   // ----- unsigned short -----
   QRS_EXPORT QVariant createArg(unsigned short val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, unsigned short& res);

   // ----- unsigned char -----
   QRS_EXPORT QVariant createArg(unsigned char val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, unsigned char& res);

   // ----- long long -----
   QRS_EXPORT QVariant createArg(long long val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, long long& res);

   // ----- long -----
   QRS_EXPORT QVariant createArg(long val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, long& res);

   // ----- int -----
   QRS_EXPORT QVariant createArg(int val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, int& res);

   // ----- short -----
   QRS_EXPORT QVariant createArg(short val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, short& res);

   // ----- signed char -----
   QRS_EXPORT QVariant createArg(signed char val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, signed char& res);

   // ----- char -----
   QRS_EXPORT QVariant createArg(char val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, char& res);

   // ----- bool -----
   QRS_EXPORT QVariant createArg(bool val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, bool& res);

   // ----- QChar -----
   QRS_EXPORT QVariant createArg(QChar val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, QChar& res);

   // ----- QString -----
   QRS_EXPORT QVariant createArg(const QString& val);
   QRS_EXPORT bool getArgValue(const QVariant& arg, QString& res);

   // ----- QList -----
   template<typename T>
   QRS_EXPORT QVariant createArg(const QList<T>& val) {
      QVariantList res;
      foreach(T t, val) {
         res.append( createArg(t) );
      }
      return QVariant(res);
   }

   template<typename T>
   QRS_EXPORT bool getArgValue(const QVariant& arg, QList<T>& res) {
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
   QRS_EXPORT QVariant createArg(const QMap<QString,T>& val) {
      QVariantMap res;
      typename QMap<QString,T>::const_iterator indx = val.begin();
      while ( indx != val.end() ) {
         res[indx.key()] = createArg(indx.value());
         indx++;
      }
      return QVariant(res);
   }

   template<typename T>
   QRS_EXPORT bool getArgValue(const QVariant& arg, QMap<QString,T>& res) {
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
