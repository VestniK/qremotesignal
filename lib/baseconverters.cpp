/**
 * @file baseconverters.cpp
 * @brief A set of converters from and to QtSoapType
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 10 Jul 2009
 */
#include "baseconverters.h"

#include <limits>

namespace qrs {
   ////////////////////////////////////////////////////////////////////////////////
   ///////////////////////// Unsigned integer numbers /////////////////////////////
   ////////////////////////////////////////////////////////////////////////////////

   // ----- unsigned long long -----
   QVariant createArg(unsigned long long val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, unsigned long long& res) {
      if ( !arg.canConvert<unsigned long long>() ) {
         return false;
      }
      if ( arg.type() == QVariant::Double ) {
         return false;
      }
      bool convRes = false;
      res = arg.toULongLong(&convRes);
      return convRes;
   }

   // ----- unsigned long -----
   QVariant createArg(unsigned long val) {
      return QVariant( (unsigned long long)val );
   }

   bool getArgValue(const QVariant& arg, unsigned long& res) {
      unsigned long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num >  std::numeric_limits<unsigned long>::max() ) {
         return false;
      }
      res = (unsigned long)num;
      return true;
   }

   // ----- unsigned -----
   QVariant createArg(unsigned val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, unsigned& res) {
      unsigned long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num > std::numeric_limits<unsigned>::max() ) {
         return false;
      }
      res = (unsigned)num;
      return true;
   }

   // ----- unsigned short -----
   QVariant createArg(unsigned short val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, unsigned short& res) {
      unsigned long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num > std::numeric_limits<unsigned short>::max() ) {
         return false;
      }
      res = (unsigned short)num;
      return true;
   }

   // ----- unsigned char -----
   QVariant createArg(unsigned char val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, unsigned char& res) {
      unsigned long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num > std::numeric_limits<unsigned char>::max() ) {
         return false;
      }
      res = (unsigned char)num;
      return true;
   }

   ///////////////////////////////////////////////////////////////////////////////
   ///////////////////////////// Signed integer numbers //////////////////////////
   ///////////////////////////////////////////////////////////////////////////////

   // ----- long long -----
   QVariant createArg(long long val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, long long& res) {
      if ( !arg.canConvert<long long>() ) {
         return false;
      }
      if ( arg.type() == QVariant::Double ) {
         return false;
      }
      if ( arg.type() == QVariant::ULongLong ) {
         unsigned long long num;
         if ( !getArgValue(arg,num) ) {
            return false; // unexpected error
         }
         if ( num > std::numeric_limits<long long>::max() ) {
            return false;
         }
      }
      bool convRes = false;
      res = arg.toLongLong(&convRes);
      return convRes;
   }

   // ----- long -----
   QVariant createArg(long val) {
      return QVariant( (long long)val );
   }

   bool getArgValue(const QVariant& arg, long& res) {
      long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num < std::numeric_limits<long>::min() ||
           num > std::numeric_limits<long>::max() ) {
         return false;
      }
      res = (long)num;
      return true;
   }

   // ----- int -----
   QVariant createArg(int val) {
      return QVariant( val );
   }

   bool getArgValue(const QVariant& arg, int& res) {
      long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num < std::numeric_limits<int>::min() ||
           num > std::numeric_limits<int>::max() ) {
         return false;
      }
      res = (int)num;
      return true;
   }

   // ----- short -----
   QVariant createArg(short val) {
      return QVariant( val );
   }

   bool getArgValue(const QVariant& arg, short& res) {
      long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num < std::numeric_limits<short>::min() ||
           num > std::numeric_limits<short>::max() ) {
         return false;
      }
      res = (short)num;
      return true;
   }

   // ----- char -----
   QVariant createArg(char val) {
      return QVariant( val );
   }

   bool getArgValue(const QVariant& arg, char& res) {
      long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num < std::numeric_limits<char>::min() ||
           num > std::numeric_limits<char>::max() ) {
         return false;
      }
      res = (char)num;
      return true;
   }

   // ----- signed char -----
   QVariant createArg(signed char val) {
      return QVariant( val );
   }

   bool getArgValue(const QVariant& arg, signed char& res) {
      long long num;
      if ( !getArgValue(arg,num) ) {
         return false;
      }
      if ( num < std::numeric_limits<signed char>::min() ||
           num > std::numeric_limits<signed char>::max() ) {
         return false;
      }
      res = (signed char)num;
      return true;
   }

   //////////////////////////////////////////////////////////////////////////////////
   ///////////////////// Unicode strings and literals ///////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////

   // QChar
   QVariant createArg(QChar val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, QChar& res) {
      if ( !arg.canConvert<QChar>() ) {
         return false;
      }
      res = arg.toChar();
      return true;
   }

   // string
   QVariant createArg(const QString& val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, QString& res) {
      if ( !arg.canConvert<QString>() ) {
         return false;
      }
      res = arg.toString();
      return true;
   }

}
