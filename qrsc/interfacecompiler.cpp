/**
 * @file interfacecompiler.cpp
 * @brief InterfaceCompiler class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 5 Aug 2009
 */
#include "interfacecompiler.h"

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QFileInfo>

#include <QtXmlPatterns/QXmlQuery>

#include "config.h"
#include "qtextserializer.h"

bool InterfaceCompiler::compileServiceHeader() {
   QFile xsltFile(":/ServiceHeader.xsl");
   QFile out(mInterface->serviceHeader());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   return xsltTransformation(out,xsltFile);
}

bool InterfaceCompiler::compileServiceSource() {
   QFile xsltFile(":/ServiceSource.xsl");
   QFile out(mInterface->serviceSource());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   return xsltTransformation(out,xsltFile);
}

bool InterfaceCompiler::compileClientHeader() {
   QFile xsltFile(":/ClientHeader.xsl");
   QFile out(mInterface->clientHeader());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   return xsltTransformation(out,xsltFile);
}

bool InterfaceCompiler::compileClientSource() {
   QFile xsltFile(":/ClientSource.xsl");
   QFile out(mInterface->clientSource());
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   out.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate);

   return xsltTransformation(out,xsltFile);
}

bool InterfaceCompiler::xsltTransformation(QFile &dest, QFile &xsltFile) {
   mInterface->getIODevice()->seek(0);
   QXmlQuery query(QXmlQuery::XSLT20);
   // Bind variables
   query.bindVariable( "QRSC_VERSION",
                       QXmlItem(QVariant(VERSION)) );
   query.bindVariable( "SRC_INTERFACE",
                       QXmlItem(QVariant(mInterface->sourceName())) );
   QFileInfo serviceHeaderInfo(mInterface->serviceHeader());
   query.bindVariable( "ServiceHeader",
                       QXmlItem(QVariant(serviceHeaderInfo.fileName())) );
   QFileInfo clientHeaderInfo(mInterface->clientHeader());
   query.bindVariable( "ClientHeader",
                       QXmlItem(QVariant(clientHeaderInfo.fileName())) );
   // prepare query
   query.setFocus(mInterface->getIODevice());
   query.setQuery(&xsltFile);
   // Transform
   QTextSerializer serializer(query,&dest);
   if ( !query.evaluateTo(&serializer) ) {
      /// @todo Produce some fail information
      return false;
   }
   return true;
}
