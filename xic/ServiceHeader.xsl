<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>
<xsl:template match="/">#ifndef _<xsl:value-of select="//interface/@name"/>Service_H
#define _<xsl:value-of select="//interface/@name"/>Service_H

#include &lt;QtCore&gt;
#include &lt;QtSoapType&gt;
#include &lt;QRemoteSignal&gt;

class <xsl:value-of select="//interface/@name"/>Service : public AbsService {
   Q_OBJECT
   public:
      <xsl:value-of select="//interface/@name"/>Service ( QObject* parent=0 ): AbsService ( parent ) {};
      <xsl:value-of select="//interface/@name"/>Service ( ComunicationManager* parent );
      virtual ~<xsl:value-of select="//interface/@name"/>Service() {};

      virtual const QString&amp; getUri() const {return uri;};
      virtual void processMessage ( const QtSoapType&amp; method )
            throw(IncorrectMethodException);
   signals:
<xsl:for-each select="//method">
      void <xsl:value-of select="./@name"/>(<xsl:for-each select="./param"><xsl:value-of select="./@type"/><xsl:text> </xsl:text><xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>);</xsl:for-each>

   private:
      static const QString uri;
};

#endif
</xsl:template>
</xsl:stylesheet>
