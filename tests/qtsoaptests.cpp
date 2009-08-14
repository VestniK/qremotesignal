/**
 * @file qtsoaptests.cpp
 * @brief QtSoap library tests
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 14 Aug 2009
 */
#include <QtCore>
#include <QtXml>
#include <QtTest>
#include <QtDebug>

#include <QtSoapMessage>

class QtSoapTests: public QObject {
   Q_OBJECT
   private slots:
      // Tests init
      void init() {
         in.clear();
         out.clear();
      }

      // Set method
      void methodTest_data() {
         QTest::addColumn<QString>("name");
         QTest::addColumn<QString>("uri");

         QTest::newRow("urn") << "method" << "urn:Uri";
         QTest::newRow("http") << "do" << "http://example.org";
      }
      void methodTest() {
         QFETCH(QString, name);
         QFETCH(QString, uri);

         out.setMethod(name,uri);
         QCOMPARE(out.method().name().name(), name);
         QCOMPARE(out.method().name().uri(),  uri);
         QDomDocument xml;
         xml.setContent(out.toXmlString(), true);
         in.setContent(xml);
         QCOMPARE(in.method().name().name(), name);
         QCOMPARE(in.method().name().uri(),  uri);
      }

      // args
      void argsTest_data() {
         QTest::addColumn<QString>("StrArgName");
         QTest::addColumn<QString>("StrVal");
         QTest::addColumn<QString>("IntArgName");
         QTest::addColumn<int>("IntVal");

         QTest::newRow("1") << "name" << "Jhon Smith" << "Age" << 23;
      }
      void argsTest() {
         QFETCH(QString, StrArgName);
         QFETCH(QString, StrVal);
         QFETCH(QString, IntArgName);
         QFETCH(int, IntVal);

         out.setMethod("do", "urn:Test");
         out.addMethodArgument(StrArgName,"",StrVal);
         out.addMethodArgument(IntArgName,"",IntVal);
         QCOMPARE(out.method()[StrArgName].toString(), StrVal);
         QCOMPARE(out.method()[IntArgName].toInt(),    IntVal);

         QDomDocument xml;
         xml.setContent(out.toXmlString(), true);
         in.setContent(xml);
         QCOMPARE(in.method()[StrArgName].toString(), StrVal);
         QCOMPARE(in.method()[IntArgName].toInt(),    IntVal);
      }

      void arrayTest() {
         out.setMethod("do","urn:Test");
         QtSoapArray *arr = new QtSoapArray(QtSoapQName("test",""),QtSoapType::Array);
         arr->append(new QtSoapSimpleType(QtSoapQName("1",""),1) );
         arr->append(new QtSoapSimpleType(QtSoapQName("2",""),2) );
         arr->append(new QtSoapSimpleType(QtSoapQName("3",""),3) );
         out.addMethodArgument(arr);
         QCOMPARE( dynamic_cast<const QtSoapArray&>(out.method()["test"]).count() , 3 );
         for (int i=0; i<3; i++) {
            QCOMPARE(dynamic_cast<const QtSoapArray&>(out.method()["test"]).at(i).toInt(), i+1);
         }
         QDomDocument xml;
         xml.setContent(out.toXmlString(), true);
         in.setContent(xml);
         QCOMPARE( dynamic_cast<const QtSoapArray&>(in.method()["test"]).count() , 3 );
         for (int i=0; i<3; i++) {
            QCOMPARE(dynamic_cast<const QtSoapArray&>(in.method()["test"]).at(i).toInt(), i+1);
         }
      }

      void incorrectContentTest_data() {
         QTest::addColumn<QString>("incoming_xml");

         QTest::newRow("not soap") << "<root><element/></root>";
      }
      void incorrectContentTest() {
         QFETCH(QString,incoming_xml);

         QDomDocument xml;
         xml.setContent(incoming_xml,true);
         QVERIFY( !in.setContent(xml) );
         QVERIFY( in.isFault() );
      }

      void setFailTest_data() {
         QTest::addColumn<int>("faultCode");

         QTest::newRow("VersionMismatch") << (int)QtSoapMessage::VersionMismatch;
         QTest::newRow("MustUnderstand") << (int)QtSoapMessage::MustUnderstand;
         QTest::newRow("Server") << (int)QtSoapMessage::Server;
         QTest::newRow("Client") << (int)QtSoapMessage::Client;
         QTest::newRow("Other") << (int)QtSoapMessage::Other;
      }
      void setFailTest() {
         QFETCH(int,faultCode);
         QVERIFY(!out.isFault());
         out.setFaultCode( (QtSoapMessage::FaultCode)faultCode );
         QEXPECT_FAIL("Other","Not fault from QtSoap point of view",Continue);
         QVERIFY(out.isFault());
      }
   private:
      QtSoapMessage out,in;
};

QTEST_MAIN(QtSoapTests);

#include"qtsoaptests.moc"
