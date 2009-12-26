<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>

<xsl:param name="QRSC_VERSION"/>
<xsl:param name="SRC_INTERFACE"/>

<xsl:template match="/">/*
This code was generated with the qrsc utility (QRemoteSignal interface
compiler) version <xsl:value-of select="$QRSC_VERSION"/> from file:
<xsl:value-of select="$SRC_INTERFACE"/>

Do not modify this file directly. Modify interface description and
run qrsc once again.
*/
#ifndef _<xsl:value-of select="/service/@name"/>Client_H
#define _<xsl:value-of select="/service/@name"/>Client_H

#include &lt;QtCore/QObject&gt;
#include &lt;QtCore/QString&gt;

#include &lt;QRemoteSignal&gt;
<xsl:for-each select="//customTypes">
#include "<xsl:value-of select="./@header"/>"</xsl:for-each>

namespace qrs {

   class <xsl:value-of select="/service/@name"/>Client : public AbsService {
      Q_OBJECT
      public:
         explicit <xsl:value-of select="/service/@name"/>Client ( QObject* parent=0 ): AbsService(parent) {}
         explicit <xsl:value-of select="/service/@name"/>Client ( ServicesManager* parent );
         virtual ~<xsl:value-of select="/service/@name"/>Client() {}

         virtual void processMessage(const Message&amp; msg)
               throw(IncorrectMethodException);

         virtual const QString&amp; name() const {return mName;}
      public slots:
<xsl:for-each select="//slot">
         void <xsl:value-of select="./@name"/>(<xsl:for-each select="./param">const <xsl:value-of select="./@type"/>&amp; <xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>);</xsl:for-each>

      signals:
<xsl:for-each select="//signal">
         void <xsl:value-of select="./@name"/>(<xsl:for-each select="./param"><xsl:value-of select="./@type"/><xsl:text> </xsl:text><xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>);</xsl:for-each>

      private:
         Q_DISABLE_COPY(<xsl:value-of select="/service/@name"/>Client);

         static const QString mName;
   };

}

#endif
</xsl:template>
</xsl:stylesheet>