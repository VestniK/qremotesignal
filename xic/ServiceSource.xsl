<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>

<xsl:param name="ServiceHeader"/>

<xsl:template match="/">#include "<xsl:value-of select="$ServiceHeader"/>"

#include &lt;QRemoteSignal&gt;

using namespace qrs;

const QString <xsl:value-of select="/service/@name"/>Service::mName = "<xsl:value-of select="/service/@name"/>";

<xsl:value-of select="/service/@name"/>Service::<xsl:value-of select="/service/@name"/>Service ( CommunicationManager* parent ): AbsService ( parent ) {
   parent->registerService(this);
}

void <xsl:value-of select="/service/@name"/>Service::processMessage (const Message&amp; msg)
      throw(IncorrectMethodException) {
   if ( msg.service() != mName ) {
      throw( IncorrectMethodException(QString("Invalid service name: %1").arg(msg.service())) );
   }
<xsl:for-each select="//method">
   if ( msg.method() == "<xsl:value-of select="./@name"/>" ) {<xsl:for-each select="./param"><xsl:text>
      </xsl:text><xsl:value-of select="./@type"/><xsl:text> </xsl:text><xsl:value-of select="./@name"/>;
      if ( ! msg.params().contains("<xsl:value-of select="./@name"/>") ) {
         throw( IncorrectMethodException( QString("Message doesn't contain param \"%1\" required to call method \"%2\"").arg("<xsl:value-of select="./@name"/>").arg(msg.method()) ) );
      }
      if ( !qrs::getArgValue(msg.params()["<xsl:value-of select="./@name"/>"], <xsl:value-of select="./@name"/>) ) {
         throw( IncorrectMethodException( QString("Can't obtain \"%1\" param value").arg("<xsl:value-of select="./@name"/>") ) );
      }</xsl:for-each>
      emit <xsl:value-of select="./@name"/>( <xsl:for-each select="./param"><xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each> );
      return;
   }</xsl:for-each>

   throw( IncorrectMethodException( QString("Unknown method %1").arg(msg.method()) ) );
}
</xsl:template>
</xsl:stylesheet>
