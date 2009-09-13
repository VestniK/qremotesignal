/**
 * @file interfacecompiler.cpp
 * @brief InterfaceCompiler class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Aug 2009
 */
#include "interfacecompiler.h"

#include <QtCore>
#include <QtXmlPatterns>

#include "qtextserializer.h"

bool InterfaceCompiler::compileServiceHeader() {
   QFile xsltFile(":/ServiceHeader.xsl");
   QFile out(mInterface->serviceHeader());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   mInterface->getIODevice()->seek(0);
   QXmlQuery query(QXmlQuery::XSLT20);
   query.setFocus(mInterface->getIODevice());
   query.setQuery(&xsltFile);

   QTextSerializer serializer(query,&out);
   if ( !query.evaluateTo(&serializer) ) {
      /// @todo Produce some fail information
      return false;
   }
   return true;
}

bool InterfaceCompiler::compileServiceSource() {
   QFile xsltFile(":/ServiceSource.xsl");
   QFile out(mInterface->serviceSource());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   mInterface->getIODevice()->seek(0);
   QXmlQuery query(QXmlQuery::XSLT20);
   QFileInfo headerInfo(mInterface->serviceHeader());
   query.bindVariable( "ServiceHeader",QXmlItem(QVariant(headerInfo.fileName())) );
   query.setFocus(mInterface->getIODevice());
   query.setQuery(&xsltFile);

   QTextSerializer serializer(query,&out);
   if ( !query.evaluateTo(&serializer) ) {
      /// @todo Produce some fail information
      return false;
   }
   return true;
}

bool InterfaceCompiler::compileClientHeader() {
   QFile xsltFile(":/ClientHeader.xsl");
   QFile out(mInterface->clientHeader());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   mInterface->getIODevice()->seek(0);
   QXmlQuery query(QXmlQuery::XSLT20);
   query.setFocus(mInterface->getIODevice());
   query.setQuery(&xsltFile);

   QTextSerializer serializer(query,&out);
   if ( !query.evaluateTo(&serializer) ) {
      /// @todo Produce some fail information
      return false;
   }
   return true;
}

bool InterfaceCompiler::compileClientSource() {
   QFile xsltFile(":/ClientSource.xsl");
   QFile out(mInterface->clientSource());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   mInterface->getIODevice()->seek(0);
   QXmlQuery query(QXmlQuery::XSLT20);
   QFileInfo headerInfo(mInterface->clientHeader());
   query.bindVariable( "ClientHeader",QXmlItem(QVariant(headerInfo.fileName())) );
   query.setFocus(mInterface->getIODevice());
   query.setQuery(&xsltFile);

   QTextSerializer serializer(query,&out);
   if ( !query.evaluateTo(&serializer) ) {
      /// @todo Produce some fail information
      return false;
   }
   return true;
}
