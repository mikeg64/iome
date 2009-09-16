<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
<xsl:template match="/">
<html>

<body >

<xsl:for-each select="iosim/simulation/metadatalist/metadata">
		<xsl:apply-templates select = "metadata" />

</xsl:for-each>

<xsl:for-each select="iosim/simulation/props/prop">
<!--<xsl:attribute  name = "name" >
                                                                                      
                                                                  </xsl:attribute>-->
	
<!--	<xsl:variable name = "" select = "" />-->
<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="@name" /></font>
		<xsl:apply-templates select = "float" />
	
	
		<xsl:apply-templates select = "int" />
	
	
		<xsl:apply-templates select = "string" />
	
</xsl:for-each>

</body>

</html>
</xsl:template>




<xsl:template match="float">

<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>


                                                                                      
</xsl:template>


<xsl:template match="int">
<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>

</xsl:template>

<xsl:template match="string">
<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>

</xsl:template>

<xsl:template match="metadata">
<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /><xsl:value-of select="@name" />  <xsl:value-of select="@property" /></font><br/>

</xsl:template>
</xsl:stylesheet>


