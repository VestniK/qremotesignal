<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>

<xsl:param name="ClientHeader"/>

<xsl:template match="/">#include "<xsl:value-of select="$ClientHeader"/>"

#include &lt;QtSoapMessage&gt;
#include &lt;QRemoteSignal&gt;
<xsl:for-each select="//customTypes">
#include "<xsl:value-of select="./@header"/>"</xsl:for-each>

using namespace qrs;

const QString <xsl:value-of select="//interface/@name"/>Client::uri = "<xsl:value-of select="//interface/@uri"/>";

<xsl:for-each select="//method">void <xsl:value-of select="//interface/@name"/>Client::<xsl:value-of select="./@name"/>(<xsl:for-each select="./param">const <xsl:value-of select="./@type"/>&amp; <xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>) {
   if ( mCManager == 0 ) {
      return;
   }
   QtSoapMessage msg;
   msg.setMethod("<xsl:value-of select="./@name"/>",uri);
<xsl:for-each select="./param">   msg.addMethodArgument( qrs::createArg("<xsl:value-of select="./@name"/>",<xsl:value-of select="./@name"/>) );
</xsl:for-each>
   mCManager->sendMessage(msg);
}

</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
