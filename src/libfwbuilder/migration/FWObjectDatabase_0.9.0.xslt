<!--
   Filename:     0.9.0/FWObjectDatabase.xslt
   Author:       Vadim Kurland
   Build date:   05/10/2001
   Last changed: 05/10/2001
   Version:      1.0.0
   Description:  translates fwbuilder object database from v0.9.0 to v0.9.1
                 This transformation only changes version number.
-->

<xsl:stylesheet version="1.0"
       xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
>


<xsl:output method="xml" version="1.0" 
   doctype-system="fwbuilder_preferences.dtd" indent="yes" encoding="utf-8"/>

<xsl:template match="FWObjectDatabase">
  <FWObjectDatabase version="0.9.1">
  <xsl:copy-of select="*"/>
  </FWObjectDatabase>
</xsl:template>

</xsl:stylesheet>

