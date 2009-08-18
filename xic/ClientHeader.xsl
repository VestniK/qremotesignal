<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="2.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:output method="text" encoding="UTF-8" media-type="text/plain"/>
<xsl:template match="/">#ifndef _<xsl:value-of select="//interface/@name"/>Client_H
#define _<xsl:value-of select="//interface/@name"/>Client_H

#include &lt;QtCore&gt;
#include &lt;QRemoteSignal&gt;

namespace qrs {

   class <xsl:value-of select="//interface/@name"/>Client : public QObject {
      Q_OBJECT
      public:
         <xsl:value-of select="//interface/@name"/>Client ( QObject* parent=0 ): QObject(parent) {mCManager = 0;};
         <xsl:value-of select="//interface/@name"/>Client ( ComunicationManager* parent ): QObject(parent) {mCManager = parent;};
         virtual ~<xsl:value-of select="//interface/@name"/>Client() {};

         void setManager(ComunicationManager* manager) {mCManager = manager;};
         ComunicationManager* getManager() {return mCManager;};
         const ComunicationManager* getManager() const {return mCManager;};

         virtual const QString&amp; getUri() const {return uri;};
      public slots:
<xsl:for-each select="//method">
         void <xsl:value-of select="./@name"/>(<xsl:for-each select="./param">const <xsl:value-of select="./@type"/>&amp; <xsl:value-of select="./@name"/><xsl:if test="position()!=last()">, </xsl:if></xsl:for-each>);</xsl:for-each>

      private:
         ComunicationManager *mCManager;
         static const QString uri;
   };

}

#endif
</xsl:template>
</xsl:stylesheet>
