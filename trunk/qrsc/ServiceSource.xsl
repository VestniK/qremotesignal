<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>

<xsl:param name="ServiceHeader"/>
<xsl:param name="QRSC_VERSION"/>
<xsl:param name="SRC_INTERFACE"/>

<xsl:template match="/">/*
This code was generated with the qrsc utility (QRemoteSignal interface
compiler) version <xsl:value-of select="$QRSC_VERSION"/> from file:
<xsl:value-of select="$SRC_INTERFACE"/>

Do not modify this file directly. Modify interface description and
run qrsc once again.
*/
#include "<xsl:value-of select="$ServiceHeader"/>"

#include &lt;QRemoteSignal&gt;

using namespace qrs;

const QString <xsl:value-of select="/service/@name"/>Service::mName = "<xsl:value-of select="/service/@name"/>";

<xsl:value-of select="/service/@name"/>Service::<xsl:value-of select="/service/@name"/>Service ( ServicesManager* parent ): AbsService ( parent ) {
   parent->registerService(this);
}

<xsl:for-each select="//signal">void <xsl:value-of select="/service/@name"/>Service::<xsl:value-of select="./@name"/>(<xsl:for-each select="./param">const <xsl:value-of select="./@type"/>&amp; <xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>) {
   if ( manager() == 0 ) {
      return;
   }
   Message msg;
   msg.setMethod("<xsl:value-of select="./@name"/>");
   msg.setService(mName);
<xsl:for-each select="./param">   msg.params().insert("<xsl:value-of select="./@name"/>",qrs::createArg(<xsl:value-of select="./@name"/>));
</xsl:for-each>
   manager()->send(msg);
}

</xsl:for-each>
void <xsl:value-of select="/service/@name"/>Service::processMessage (const Message&amp; msg)
      throw(IncorrectMethodException) {
   if ( msg.service() != mName ) {
      throw( IncorrectMethodException(AbsService::tr("Invalid service name: %1").arg(msg.service())) );
   }
<xsl:for-each select="//slot">
   if ( msg.method() == "<xsl:value-of select="./@name"/>" ) {<xsl:for-each select="./param"><xsl:text>
      </xsl:text><xsl:value-of select="./@type"/><xsl:text> </xsl:text><xsl:value-of select="./@name"/>;
      if ( ! msg.params().contains("<xsl:value-of select="./@name"/>") ) {
         throw( IncorrectMethodException( AbsService::tr("Message doesn't contain param \"%1\" required to call method \"%2\"").arg("<xsl:value-of select="./@name"/>").arg(msg.method()) ) );
      }
      if ( !qrs::getArgValue(msg.params()["<xsl:value-of select="./@name"/>"], <xsl:value-of select="./@name"/>) ) {
         throw( IncorrectMethodException( AbsService::tr("Can't obtain \"%1\" param value").arg("<xsl:value-of select="./@name"/>") ) );
      }</xsl:for-each>
      emit <xsl:value-of select="./@name"/>( <xsl:for-each select="./param"><xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each> );
      return;
   }</xsl:for-each>

   throw( IncorrectMethodException( AbsService::tr("Unknown method %1").arg(msg.method()) ) );
}
</xsl:template>
</xsl:stylesheet>
