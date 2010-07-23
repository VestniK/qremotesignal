/**
 * @file baseconverters.h
 * @brief Set of convertors of different types from and to Message argumenat
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#ifndef _BaseConverters_H
#define _BaseConverters_H

#include <QtCore/QString>
#include <QtCore/QChar>
#include <QtCore/QList>
#include <QtCore/QMap>

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

   // Template convertors forward declaratin
   template<typename T>
   QVariant createArg(const QList<T>& val);

   template<typename T>
   bool getArgValue(const QVariant& arg, QList<T>& res);

   template<typename T>
   QVariant createArg(const QMap<QString,T>& val);

   template<typename T>
   bool getArgValue(const QVariant& arg, QMap<QString,T>& res);

}

#endif
