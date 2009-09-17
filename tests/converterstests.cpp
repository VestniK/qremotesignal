/**
 * @file converterstests.cpp
 * @brief Base converters tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 17 Sep 2009
 */
#include "baseconverters.h"

#include <limits.h>

#include <QtCore>
#include <QtTest>

#include <QtDebug>

typedef QMap<QString,int> QIntMap;

Q_DECLARE_METATYPE(QVariant);
Q_DECLARE_METATYPE(QList<int>);
Q_DECLARE_METATYPE(QIntMap);

class ConvertersTests: public QObject {
   Q_OBJECT
   private slots:
      void initTestCase() {
         qRegisterMetaType<QVariant>("QVariant");
         qRegisterMetaType< QList<int> >("QList<int>");
         qRegisterMetaType< QMap<QString,int> >("QMap<QString,int>");
      }

      // int
      void testConvertInt_data() {
         QTest::addColumn<int>("src");

         QTest::newRow("1") << 1;
         QTest::newRow("-100") << -100;
         QTest::newRow("0") << 0;
         QTest::newRow("32000") << 32000;
      }
      void testConvertInt() {
         QFETCH(int,src);

         int res;
         QVERIFY( qrs::getArgValue(qrs::createArg(src),res) );
         QCOMPARE(res,src);
      }

      void testInvalidConvertToInt_data() {
         QTest::addColumn<QVariant>("arg");

         QTest::newRow("string") << QVariant("not a number");
         QTest::newRow("out of range") << QVariant( (long long)INT_MAX + 100ll );
         QTest::newRow("double") << QVariant( 1.75 );
         QTest::newRow("string with double") << QVariant("2.34");
         QTest::newRow("string number out of range")
               << QVariant( QString::number((long long)INT_MAX + 100ll) );

         QVariantList list;
         list.append(QVariant(1));
         list.append(QVariant(2));
         list.append(QVariant(3));
         QTest::newRow("list") << QVariant(list);
      }
      void testInvalidConvertToInt() {
         QFETCH(QVariant,arg);

         int res;
         QVERIFY( !qrs::getArgValue(arg,res) );
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

         QMap<QString,int> map;
         map["one"] = 1;
         map["two"] = 2;
         map["three"] = 3;
         QTest::newRow("simple") << map;
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
