<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>

<xsl:param name="ServiceHeader"/>

<xsl:template match="/">#include "<xsl:value-of select="$ServiceHeader"/>"

#include &lt;QRemoteSignal&gt;

using namespace qrs;

const QString <xsl:value-of select="/service/@name"/>Service::mName = "<xsl:value-of select="/service/@name"/>";

<xsl:value-of select="/service/@name"/>Service::<xsl:value-of select="/service/@name"/>Service ( ComunicationManager* parent ): AbsService ( parent ) {
   parent->registerService(this);
}

void <xsl:value-of select="/service/@name"/>Service::processMessage (const RemoteCall&amp; rc)
      throw(IncorrectMethodException) {
   if ( rc.service() != mName ) {
      throw( IncorrectMethodException(QString("Invalid service name: %1").arg(rc.service())) );
   }
<xsl:for-each select="//method">
   if ( rc.method() == "<xsl:value-of select="./@name"/>" ) {<xsl:for-each select="./param"><xsl:text>
      </xsl:text><xsl:value-of select="./@type"/><xsl:text> </xsl:text><xsl:value-of select="./@name"/>;
      if ( !qrs::getArgValue(rc, "<xsl:value-of select="./@name"/>", <xsl:value-of select="./@name"/>) ) {
         throw( IncorrectMethodException( QString("Can't obtain \"%1\" param value").arg("<xsl:value-of select="./@name"/>") ) );
      }</xsl:for-each>
      emit <xsl:value-of select="./@name"/>( <xsl:for-each select="./param"><xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each> );
      return;
   }</xsl:for-each>

   throw( IncorrectMethodException( QString("Unknown method %1").arg(rc.method()) ) );
}
</xsl:template>
</xsl:stylesheet>
