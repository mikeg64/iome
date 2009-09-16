<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:fo="http://www.w3.org/1999/XSL/Format">
<xsl:template match="/">
<html>

<body >
<h1><font  color="#993333" size="4" face="Trebushet MS">Shallow Water Simulation</font>
</h1>

<h2><font  color="#993333" size="4" face="Trebushet MS">Metadata</font>
</h2>

<table>
	<tbody>
	<tr>
			<th><font  color="#993333" size="4" face="Trebushet MS">Name</font>
</th><th><font  color="#993333" size="4" face="Trebushet MS">Value</font>
</th>

		</tr>
<xsl:for-each select="iosim/simulation/metadatalist/metadata">

		<tr>
			<td><font  color="#993333" size="4" face="Trebushet MS"><xsl:value-of select="@name" />  </font></td><td><font  color="#993333" size="4" face="Trebushet MS"><xsl:value-of select="@content" /></font></td>

		</tr>
		
</xsl:for-each>


	</tbody>
</table>


<xsl:for-each select="iosim/simulation/metadatalist">
		<br/><br/><br/>
</xsl:for-each>

<h2><font  color="#993333" size="4" face="Trebushet MS">Parameters</font>
</h2>

<table>
	<tbody>
	<tr>
			<th><font  color="#993333" size="2" face="Trebushet MS">Name</font>
</th><th><font  color="#993333" size="2" face="Trebushet MS">Value</font>
</th>

		</tr>

<xsl:for-each select="iosim/simulation/props/prop">
<!--<xsl:attribute  name = "name" >
                                                                                      
                                                                  </xsl:attribute>-->
	
<!--	<xsl:variable name = "" select = "" />-->

	<tr>
			<td><font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="@name" /></font>
</td><td><xsl:apply-templates select = "float" />
	
	
		<xsl:apply-templates select = "int" />
	
	
		<xsl:apply-templates select = "string" />
		
		<xsl:apply-templates select = "vec" />

		<xsl:apply-templates select = "mat" /></td>

		</tr>

		


	
</xsl:for-each>

	</tbody>
</table>


</body>

</html>
</xsl:template>




<xsl:template match="float">

<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>


                                                                                      
</xsl:template>

<xsl:template match="vec">

<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>


                                                                                      
</xsl:template>

<xsl:template match="mat">

<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>


                                                                                      
</xsl:template>


<xsl:template match="int">
<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>

</xsl:template>

<xsl:template match="string">
<font  color="#993333" size="2" face="Trebushet MS"><xsl:value-of select="." /></font><br/>

</xsl:template>


</xsl:stylesheet>


