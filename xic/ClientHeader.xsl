<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>
<xsl:template match="/">#ifndef _<xsl:value-of select="/service/@name"/>Client_H
#define _<xsl:value-of select="/service/@name"/>Client_H

#include &lt;QtCore&gt;
#include &lt;QRemoteSignal&gt;
<xsl:for-each select="//customTypes">
#include "<xsl:value-of select="./@header"/>"</xsl:for-each>

namespace qrs {

   class <xsl:value-of select="/service/@name"/>Client : public QObject {
      Q_OBJECT
      public:
         <xsl:value-of select="/service/@name"/>Client ( QObject* parent=0 ): QObject(parent) {mCManager = 0;};
         <xsl:value-of select="/service/@name"/>Client ( CommunicationManager* parent ): QObject(parent) {mCManager = parent;};
         virtual ~<xsl:value-of select="/service/@name"/>Client() {};

         void setManager(CommunicationManager* val) {mCManager = val;};
         CommunicationManager* manager() {return mCManager;};
         const CommunicationManager* manager() const {return mCManager;};

         virtual const QString&amp; name() const {return mName;};
      public slots:
<xsl:for-each select="//method">
         void <xsl:value-of select="./@name"/>(<xsl:for-each select="./param">const <xsl:value-of select="./@type"/>&amp; <xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>);</xsl:for-each>

      private:
         CommunicationManager *mCManager;
         static const QString mName;
   };

}

#endif
</xsl:template>
</xsl:stylesheet>
