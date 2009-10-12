/**
 * @file converterstests.cpp
 * @brief Base converters tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 17 Sep 2009
 */
#include "baseconverters.h"

#include <limits>

#include <QtCore>
#include <QtTest>

#include <QtDebug>

typedef QMap<QString,int> QIntMap;

Q_DECLARE_METATYPE(QVariant);
Q_DECLARE_METATYPE(QList<int>);
Q_DECLARE_METATYPE(QIntMap);
Q_DECLARE_METATYPE(signed char);

class ConvertersTests: public QObject {
   Q_OBJECT
   private slots:
      void initTestCase() {
         qRegisterMetaType<QVariant>("QVariant");
         qRegisterMetaType< QList<int> >("QList<int>");
         qRegisterMetaType< QMap<QString,int> >("QMap<QString,int>");
         qRegisterMetaType<signed char>("signed char");
      }

      // QChar
      void testConvertQChar_data() {
         QTest::addColumn<QChar>("src");

         QTest::newRow("1") << QChar('1');
         QTest::newRow("null") << QChar('\0');
         QTest::newRow("latin") << QChar('l');
      }
      void testConvertQChar() {
         QFETCH(QChar,src);

         QChar res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // char
      void testConvertChar_data() {
         QTest::addColumn<char>("src");

         QTest::newRow("a") << 'a';
         QTest::newRow("b") << 'b';
         QTest::newRow("0") << '0';
         QTest::newRow("null") << '\0';
         QTest::newRow("min") << std::numeric_limits<char>::min();
         QTest::newRow("max") << std::numeric_limits<char>::max();
      }
      void testConvertChar() {
         QFETCH(char,src);

         char res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // signed char
      void testConvertSignedChar_data() {
         QTest::addColumn<signed char>("src");

         QTest::newRow("-1") << (signed char)-1;
         QTest::newRow("0") << (signed char)0;
         QTest::newRow("1") << (signed char)1;
         QTest::newRow("min") << std::numeric_limits<signed char>::min();
         QTest::newRow("max") << std::numeric_limits<signed char>::max();
      }
      void testConvertSignedChar() {
         QFETCH(signed char,src);

         signed char res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // unsigned char
      void testConvertUnsignedChar_data() {
         QTest::addColumn<unsigned char>("src");

         QTest::newRow("0") << (unsigned char)0;
         QTest::newRow("1") << (unsigned char)1;
         QTest::newRow("min") << std::numeric_limits<unsigned char>::min();
         QTest::newRow("max") << std::numeric_limits<unsigned char>::max();
      }
      void testConvertUnsignedChar() {
         QFETCH(unsigned char,src);

         unsigned char res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // short
      void testConvertShort_data() {
         QTest::addColumn<short>("src");

         QTest::newRow("min") << std::numeric_limits<short>::min();
         QTest::newRow("-1") << (short)-1;
         QTest::newRow("0") << (short)0;
         QTest::newRow("1") << (short)1;
         QTest::newRow("max") << std::numeric_limits<short>::max();
      }
      void testConvertShort() {
         QFETCH(short,src);

         short res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // unsigned short
      void testConvertUShort_data() {
         QTest::addColumn<unsigned short>("src");

         QTest::newRow("min") << std::numeric_limits<unsigned short>::min();
         QTest::newRow("0") << (unsigned short)0;
         QTest::newRow("1") << (unsigned short)1;
         QTest::newRow("max") << std::numeric_limits<unsigned short>::max();
      }
      void testConvertUShort() {
         QFETCH(unsigned short,src);

         unsigned short res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // int
      void testConvertInt_data() {
         QTest::addColumn<int>("src");

         QTest::newRow("1") << 1;
         QTest::newRow("-100") << -100;
         QTest::newRow("0") << 0;
         QTest::newRow("32000") << 32000;
         QTest::newRow("min") << std::numeric_limits<int>::min();
         QTest::newRow("max") << std::numeric_limits<int>::max();
      }
      void testConvertInt() {
         QFETCH(int,src);

         int res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // unsigned
      void testConvertUnsigned_data() {
         QTest::addColumn<unsigned>("src");

         QTest::newRow("1") << 1u;
         QTest::newRow("0") << 0u;
         QTest::newRow("32000") << 32000u;
         QTest::newRow("min") << std::numeric_limits<unsigned>::min();
         QTest::newRow("max") << std::numeric_limits<unsigned>::max();
      }
      void testConvertUnsigned() {
         QFETCH(unsigned,src);

         unsigned res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // long
      void testConvertLong_data() {
         QTest::addColumn<long>("src");

         QTest::newRow("-1") << -1l;
         QTest::newRow("1") << 1l;
         QTest::newRow("0") << 0l;
         QTest::newRow("min") << std::numeric_limits<long>::min();
         QTest::newRow("max") << std::numeric_limits<long>::max();
      }
      void testConvertLong() {
         QFETCH(long,src);

         long res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // long long
      void testConvertLLong_data() {
         QTest::addColumn<long long>("src");

         QTest::newRow("-1") << -1ll;
         QTest::newRow("1") << 1ll;
         QTest::newRow("0") << 0ll;
         QTest::newRow("min") << std::numeric_limits<long long>::min();
         QTest::newRow("max") << std::numeric_limits<long long>::max();
      }
      void testConvertLLong() {
         QFETCH(long long,src);

         long long res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // unsigned long
      void testConvertULong_data() {
         QTest::addColumn<unsigned long>("src");

         QTest::newRow("1") << 1ul;
         QTest::newRow("0") << 0ul;
         QTest::newRow("min") << std::numeric_limits<unsigned long>::min();
         QTest::newRow("max") << std::numeric_limits<unsigned long>::max();
      }
      void testConvertULong() {
         QFETCH(unsigned long,src);

         unsigned long res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      // unsigned long long
      void testConvertULLong_data() {
         QTest::addColumn<unsigned long long>("src");

         QTest::newRow("1") << 1ull;
         QTest::newRow("0") << 0ull;
         QTest::newRow("min") << std::numeric_limits<unsigned long long>::min();
         QTest::newRow("max") << std::numeric_limits<unsigned long long>::max();
      }
      void testConvertULLong() {
         QFETCH(unsigned long long,src);

         unsigned long long res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      void testInvalidConvertToInteger_data() {
         QTest::addColumn<QVariant>("arg");

         QTest::newRow("string") << QVariant("not a number");
         QTest::newRow("out of range") << QVariant( std::numeric_limits<unsigned long long>::max() );
         QTest::newRow("double") << QVariant( 1.75 );
         QTest::newRow("string with double") << QVariant("2.34");
         QTest::newRow("string number out of range")
               << QVariant( QString::number(std::numeric_limits<unsigned long long>::max()).append("00") );

         QVariantList list;
         list.append(QVariant(1));
         list.append(QVariant(2));
         list.append(QVariant(3));
         QTest::newRow("list") << QVariant(list);
      }
      void testInvalidConvertToInteger() {
         QFETCH(QVariant,arg);

         char charRes;
         QVERIFY( !qrs::getArgValue(arg,charRes) );
         signed char scharRes;
         QVERIFY( !qrs::getArgValue(arg,scharRes) );
         unsigned char ucharRes;
         QVERIFY( !qrs::getArgValue(arg,ucharRes) );
         short shortRes;
         QVERIFY( !qrs::getArgValue(arg,shortRes) );
         unsigned short ushortRes;
         QVERIFY( !qrs::getArgValue(arg,ushortRes) );
         int intRes;
         QVERIFY( !qrs::getArgValue(arg,intRes) );
         unsigned unsignedRes;
         QVERIFY( !qrs::getArgValue(arg,unsignedRes) );
         long longRes;
         QVERIFY( !qrs::getArgValue(arg,longRes) );
         unsigned long ulongRes;
         QVERIFY( !qrs::getArgValue(arg,ulongRes) );
         long long longlongRes;
         QVERIFY( !qrs::getArgValue(arg,longlongRes) );
         unsigned long long ulonglongRes;
         QEXPECT_FAIL("out of range","All ok this check should fail",Continue);
         QVERIFY( !qrs::getArgValue(arg,ulonglongRes) );
      }

      // bool
      void testConvertBool() {
         bool src,res;

         src = true;
         QVERIFY( qrs::getArgValue(qrs::createArg(src), res) );
         QCOMPARE(res,src);

         src = false;
         QVERIFY( qrs::getArgValue(qrs::createArg(src), res) );
         QCOMPARE(res,src);
      }

      // QString
      void testConvertStr_data() {
         QTest::addColumn<QString>("src");

         QTest::newRow("word") << "word";
         QTest::newRow("line") << "Some line";
         QTest::newRow("two lines") << "Multiline string\nthere are 2 lines";
      }
      void testConvertStr() {
         QFETCH(QString,src);

         QString res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      void testInvalidConvertToStr_data() {
         QTest::addColumn<QVariant>("arg");

         QVariantList list;
         list.append( QVariant("first") );
         list.append( QVariant("second") );
         QTest::newRow("list") << QVariant(list);

         QVariantMap map;
         map["one"] = QVariant("1");
         map["two"] = QVariant("2");
         QTest::newRow("map") << QVariant(map);
      }
      void testInvalidConvertToStr() {
         QFETCH(QVariant,arg);

         QString res;
         QVERIFY( !qrs::getArgValue(arg,res) );
      }

      // QList
      void testConvertList_data() {
         QTest::addColumn< QList<int> >("src");

         QTest::newRow("simple") << ( QList<int>() << 1 << 2 << 3 );
         QTest::newRow("empty") << QList<int>();
      }
      void testConvertList() {
         QFETCH(QList<int>,src);

         QList<int> res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res , src);
      }

      void testInvalidConvertToList_data() {
         QTest::addColumn<QVariant>("arg");

         QTest::newRow("string") << QVariant("string");
         QTest::newRow("int") << QVariant(15);
         QVariantMap map;
         map["one"] = QVariant("1");
         map["two"] = QVariant("2");
         QTest::newRow("map") << QVariant(map);
      }
      void testInvalidConvertToList() {
         QFETCH(QVariant,arg);

         QList<int> res;
         QVERIFY( !qrs::getArgValue(arg,res) );
      }

      // QMap
      void testConvertMap_data() {
         QTest::addColumn< QIntMap >("src");

         QIntMap map;
         map["one"] = 1;
         map["two"] = 2;
         map["three"] = 3;
         QTest::newRow("simple") << map;
         QTest::newRow("empty") << QIntMap();
      }
      void testConvertMap() {
         QFETCH(QIntMap,src);

         QIntMap res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res , src);
      }

      void testInvalidConvertToMap_data() {
         QTest::addColumn<QVariant>("arg");

         QTest::newRow("string") << QVariant("string");
         QTest::newRow("int") << QVariant(15);

         QVariantList list;
         list.append( QVariant("first") );
         list.append( QVariant("second") );
         QTest::newRow("list") << QVariant(list);
      }
      void testInvalidConvertToMap() {
         QFETCH(QVariant,arg);

         QIntMap res;
         QVERIFY( !qrs::getArgValue(arg,res) );
      }
};

#include "converterstests.moc"

QTEST_MAIN(ConvertersTests);
