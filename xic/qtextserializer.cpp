/**
 * @file qtextserializer.cpp
 * @brief Plain text serializer of QQuery processor
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 29 Jul 2009
 */
#include "qtextserializer.h"

QTextSerializer::QTextSerializer (const QXmlQuery & query, QIODevice * outputDevice) {
   mOut = outputDevice;
   mTxtCodec = QTextCodec::codecForName("UTF-8");
}

void QTextSerializer::startElement(const QXmlName &name) {
   // it looks like in case of <xsl:output method="text"/> XML elements
   // in a template file should be ignored.
}

void QTextSerializer::endElement() {
   // it looks like in case of <xsl:output method="text"/> XML elements
   // in a template file should be ignored.
}

void QTextSerializer::attribute(const QXmlName &name, const QStringRef &value) {
   // it looks like in case of <xsl:output method="text"/> XML element
   // attributes in a template file should be ignored.
}

void QTextSerializer::comment(const QString &value) {
   qDebug("void comment(const QString &value)");
}

void QTextSerializer::characters(const QStringRef &value) {
   mOut->write( mTxtCodec->fromUnicode(value.unicode(),value.count()) );
}

void QTextSerializer::startDocument() {
   qDebug("void startDocument()");
}

void QTextSerializer::endDocument() {
   qDebug("void endDocument()");
}

void QTextSerializer::processingInstruction(const QXmlName &target, const QString &value) {
   qDebug("void processingInstruction(const QXmlName &target, const QString &value)");
}

void QTextSerializer::atomicValue(const QVariant &value) {
   qDebug("void atomicValue(const QVariant &value)");
}

void QTextSerializer::namespaceBinding(const QXmlName &name) {
   // it looks like in case of <xsl:output method="text"/> XML elements
   // and namespaces in a template file should be ignored.
}

void QTextSerializer::startOfSequence() {
   // No special action required for plain text output document
}

void QTextSerializer::endOfSequence() {
   // No special action required for plain text output document
}
