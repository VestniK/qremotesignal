/**
 * @file interfacedocument.cpp
 * @brief InterfaceDocument class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Aug 2009
 */
#include "interfacedocument.h"

#include <cstdio>

#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QBuffer>
#include <QtCore/QXmlStreamReader>
#include <QtCore/QDebug>

#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlFormatter>

const QString SERVICE_ELEMENT_NAME = "service";
const QString NAME_ATTRIBUTE = "name";

const QString DEPRICATED_METHOD_TAG = "method";

InterfaceDocument::InterfaceDocument(const QString& path) {
   // Initializing members
   mInterfaceFile = new QFile(path);
   mValid = true;
   mError = "";
   mInterfaceFile->open(QIODevice::ReadOnly | QIODevice::Text);
   QFileInfo sourceInfo(path);
   mSourceName = sourceInfo.fileName();
   // Searching through the document for name and checking its consistency
   bool outdated = false;
   QXmlStreamReader xml(mInterfaceFile);
   while ( !xml.atEnd() ) {
      if ( xml.readNext() == QXmlStreamReader::StartElement ) {
         if ( xml.name().compare(SERVICE_ELEMENT_NAME,Qt::CaseInsensitive) == 0 ) {
            mName = "";
            mName.append(xml.attributes().value(NAME_ATTRIBUTE));
            continue;
         }
         if ( xml.name().compare(DEPRICATED_METHOD_TAG,Qt::CaseInsensitive) == 0 ) {
            outdated = true;
            continue;
         }
      }
   }
   // Checking for errors
   if ( xml.hasError() ) {
      mValid = false;
      mError = xml.errorString();
      return;
   }
   if ( mName.isEmpty() ) {
      mValid = false;
      mError = tr("Interface name not found");
      return;
   }
   // Updating document if necessary
   if ( outdated ) {
      qWarning() << mSourceName << tr("<method> element is deprecated use <slot> instead");
      qWarning() << tr("Hint: you can update your file using --update output_file key");
      update();
   }
   // Finalizing class initialization
   mInterfaceFile->seek(0);
   mServiceHeader = mName.toLower()+"service.h";
   mServiceSource = mName.toLower()+"service.cpp";
   mClientHeader = mName.toLower()+"client.h";
   mClientSource = mName.toLower()+"client.cpp";
}

void InterfaceDocument::update() {
   static const int INDENTATION_DEPTH = 3;
   QIODevice* oldDevice = mInterfaceFile;
   oldDevice->seek(0);
   mInterfaceFile = new QBuffer();
   mInterfaceFile->open(QIODevice::ReadWrite | QIODevice::Text);
   QFile xsltFile(":/schema_updates/UpdateTo.0.7.0.xsl");
   xsltFile.open(QIODevice::ReadOnly | QIODevice::Text);
   QXmlQuery query(QXmlQuery::XSLT20);
   query.setFocus(oldDevice);
   query.setQuery(&xsltFile);
   // Transform
   QXmlFormatter serializer(query,mInterfaceFile);
   serializer.setIndentationDepth(INDENTATION_DEPTH);
   if ( !query.evaluateTo(&serializer) ) {
      mValid = false;
      mError = tr("Updating interface failed");
   }
   delete oldDevice;
   mInterfaceFile->seek(0);
}
