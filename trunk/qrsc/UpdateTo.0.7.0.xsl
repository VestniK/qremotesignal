<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="xml" encoding="UTF-8" media-type="text/xml"/>

<xsl:template match="/service">
   <xsl:element name="service">
      <xsl:attribute name="name">
         <xsl:value-of select="/service/@name"/>
      </xsl:attribute>
      <xsl:for-each select="./*">
         <xsl:if test="name(.) = 'method'">
            <xsl:element name="slot">
               <xsl:attribute name="name"><xsl:value-of select="./@name"/></xsl:attribute>
               <xsl:copy-of select="./*"/>
            </xsl:element>
         </xsl:if>
         <xsl:if test="name(.) != 'method'"><xsl:copy-of select="."/></xsl:if>
      </xsl:for-each>
   </xsl:element>
</xsl:template>

</xsl:stylesheet>