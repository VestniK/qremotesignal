<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>

<xsl:param name="ClientHeader"/>

<xsl:template match="/">#include "<xsl:value-of select="$ClientHeader"/>"

#include &lt;QRemoteSignal&gt;

using namespace qrs;

const QString <xsl:value-of select="/service/@name"/>Client::mName = "<xsl:value-of select="/service/@name"/>";

<xsl:for-each select="//method">void <xsl:value-of select="/service/@name"/>Client::<xsl:value-of select="./@name"/>(<xsl:for-each select="./param">const <xsl:value-of select="./@type"/>&amp; <xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>) {
   if ( mCManager == 0 ) {
      return;
   }
   Message msg;
   msg.setMethod("<xsl:value-of select="./@name"/>");
   msg.setService(mName);
<xsl:for-each select="./param">   msg.params().insert("<xsl:value-of select="./@name"/>",qrs::createArg(<xsl:value-of select="./@name"/>));
</xsl:for-each>
   mCManager->send(msg);
}

</xsl:for-each>
</xsl:template>
</xsl:stylesheet>
