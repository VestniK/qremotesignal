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
         if ( num > (unsigned long long)std::numeric_limits<long long>::max() ) {
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
   //////////////////////////////////// Boolean /////////////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////

   QVariant createArg(bool val) {
      return QVariant(val);
   }

   bool getArgValue(const QVariant& arg, bool& res) {
      if ( ! arg.canConvert<bool>() ) {
         return false;
      }
      res = arg.toBool();
      return true;
   }

   //////////////////////////////////////////////////////////////////////////////////
   ///////////////////// Unicode strings and literals ///////////////////////////////
   //////////////////////////////////////////////////////////////////////////////////

   // QChar
   QVariant createArg(QChar val) {
      return QVariant(val.unicode());
   }

   bool getArgValue(const QVariant& arg, QChar& res) {
      unsigned short unicode;
      if ( !getArgValue(arg,unicode) ) {
      }
      res = QChar(unicode);
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

/**
 * @page converters Types that can be used as remote callable slots arguments
 *
 * QRemoteSignal library allows you to use a lot of types as remote callable
 * signals or slots parameters. Currently this types are available out of box:
 * @li Any integer types
 * @li @b bool
 * @li @b QChar
 * @li @b QString
 * @li @b QList<T> where T is any supported type
 * @li @b QMap<QString,T> where T is any supported type
 *
 * Also the library provides you a simple way to add support of your custom
 * type. All you need to do is create two functions:
 * @code
 * QVariant qrs::createArg(const YourType &val);
 * bool qrs::getArgValue(const QVariant &arg, YourType& res);
 * @endcode
 *
 * @li @b createArg takes value of your type and creates QVariant tree
 * containing elements of types supported by the library.
 * @li @b getArgValue takes QVariant, cheks that it contains value of your type
 * and put this value to the @b res argument. It should return @c false if it
 * can't get value of you type from @b arg parameter.
 *
 * You should specify header files with declaration of those functions for all
 * custom types which are used in signals or slots parameters in a service XML
 * description file using
 * @code <customtypes header="filename.h"/> @endcode
 * element.
 */
