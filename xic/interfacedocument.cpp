/**
 * @file interfacedocument.cpp
 * @brief InterfaceDocument class
 *
 * @author VestniK (Sergey N.Vidyuk) sir.vestnik@gmail.com
 * @date 4 Aug 2009
 */
#include "interfacedocument.h"

#include <QtXml>

#define INTERFACE_ELEMENT_NAME "interface"
#define NAME_ATTRIBUTE "name"

InterfaceDocument::InterfaceDocument(const QString& path):mInterfaseFile(path) {
   mValid = true;
   mError = "";
   mInterfaseFile.open(QIODevice::ReadOnly | QIODevice::Text);
   QXmlStreamReader xml(&mInterfaseFile);
   while ( !xml.atEnd() ) {
      if ( xml.readNext() == QXmlStreamReader::StartElement ) {
         if ( xml.name() == INTERFACE_ELEMENT_NAME ) {
            mName.append(xml.attributes().value(NAME_ATTRIBUTE));
            break;
         }
      }
   }
   if ( xml.hasError() ) {
      mValid = false;
      mError = xml.errorString();
      return;
   }
   if ( mName.isEmpty() ) {
      mValid = false;
      mError = "Interface name not found";
      return;
   }
   mInterfaseFile.seek(0);
   mServiceHeader = mName.toLower()+"service.h";
   mServiceSource = mName.toLower()+"service.cpp";
   mClientHeader = mName.toLower()+"client.h";
   mClientSource = mName.toLower()+"client.cpp";
}
