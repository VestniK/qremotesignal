<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>
<xsl:template match="/">#ifndef _<xsl:value-of select="/service/@name"/>Service_H
#define _<xsl:value-of select="/service/@name"/>Service_H

#include &lt;QtCore&gt;
#include &lt;QRemoteSignal&gt;
<xsl:for-each select="//customTypes">
#include "<xsl:value-of select="./@header"/>"</xsl:for-each>

namespace qrs {

   class <xsl:value-of select="/service/@name"/>Service : public AbsService {
      Q_OBJECT
      public:
         <xsl:value-of select="/service/@name"/>Service ( QObject* parent=0 ): AbsService ( parent ) {};
         <xsl:value-of select="/service/@name"/>Service ( ComunicationManager* parent );
         virtual ~<xsl:value-of select="/service/@name"/>Service() {};

         virtual const QString&amp; name() const {return mName;};
         virtual void processMessage ( const Message&amp; method )
               throw(IncorrectMethodException);
      signals:
<xsl:for-each select="//method">
         void <xsl:value-of select="./@name"/>(<xsl:for-each select="./param"><xsl:value-of select="./@type"/><xsl:text> </xsl:text><xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>);</xsl:for-each>

      private:
         static const QString mName;
   };

}

#endif
</xsl:template>
</xsl:stylesheet>
