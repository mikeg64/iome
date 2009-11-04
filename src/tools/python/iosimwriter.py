#!/usr/bin/python


#Run this program 
import os
import sys
import xml.dom.minidom
import xml.dom.*
class iosimwriter

    def __init__(self,simulation)
        self.simulation=simulation
    def writesimulation(filename)
        doc=self.createdomdoc(filename)
        file_object = open(filename, "w")
        xml.dom.ext.PrettyPrint(doc, file_object)
        file_object.close()
    def createdomdoc(filename)
        doc = xml.dom.minidom.Document()
        iosim_element = doc.createElement("iosim")
        iosim_element.setAttribute("filename",filename)
        simulation_element=createsimulationelement(doc)
        iosim_element.appendChild(simulation_element)
        doc.appendChild(iosim_element)
        return doc
    def createsimulationelement(doc)
        simulationelement=doc.createElement("simulation")
        propselement=createpropselement(doc)
        metadatalistelement=createmetadatalistelement(doc)
        stepselement=createstepselement(doc)
        filepropselement=createfilepropselement(doc)
        simulationelement.appendChild(propselement)
        simulationelement.appendChild(metadatalistelement)
        simulationelement.appendChild(stepselement)
        simulationelement.appendChild(filepropselement)
        return simulationelement
    def createmetadatalistelement(doc)
        simulation=self.simulation
        metadatalist=simulation.metadata
        metadatalistelement=doc.createElement("metadatalist")
        numprops=metadatalist.len()
        for n in range(0, numprops):
            metadata=metadatalist[n]
            metadataelement=createmetadataelement(doc,metadata)
            metadatalistelement.appendChild(metadataelement)
            

        return metadatalistelement
    def createmetadataelement(doc, metadata)
        metadataelement=doc.createElement("metadata")
        name=metadata.name
        property=metadata.property
        metadataelement.setAttribute("name",name)
        metadataelement.setAttribute("property",property)
        return metadataelement
    def createpropselement(doc)
        propselement=doc.createElement("props")
        simulation=self.simulation
        props=simulation.params
        numprops=props.len()
        for n in range(0, numprops):
            prop=props[n]
            propelement=createpropelement(doc,n,prop)
            propselement.appendChild(propelement)
        return propselement    
    def createpropelement(doc,index,prop)
        propelement=doc.createElement("prop")
        propelement.setAttribute("index",index)
        propelement.setAttribute("name",prop.name)
        propelement.setAttribute("flag",7)
        type=prop.ptype        
        if type="int":
            valelement=doc.createElement("int")
        elif type="float":
            valelement=doc.createElement("float")
        elif type="vec":
            valelement=doc.createElement("vec")
            valelement.setAttribute("size",prop.size)            
        elif type="string":
            valelement=doc.createElement("string")            
        elif type="mat":
            valelement=doc.createElement("mat")
            valelement.setAttribute("rows",prop.rows)            
            valelement.setAttribute("cols",prop.cols)            
        val = doc.createTextNode(prop.svalue)
        valelement.appendChild(val)
        propelement.appendChild(valelement)            
        return propelement        
    def createstepselement(doc)
        stepselement=doc.createElement("steps")
        stepselement.setAttribute("configstepfreq","1")
        stepselement.setAttribute("statestepfreq","1")
        nsteps = doc.createTextNode("10")
        stepselement.appendChild(nsteps)
        return stepselement
    def createfilepropselement(doc)
        filepropselement=doc.createElement("fileprops")
        filepropselement.setAttribute("configfilename", "configfile.xml")
        filepropselement.setAttribute("configreadmethod", "1")
        filepropselement.setAttribute("configwritemethod", "1")
        filepropselement.setAttribute("simreadmethod", "1")
        filepropselement.setAttribute("simwritemethod", "1")
        filepropselement.setAttribute("statesimfilename", "statefile.xml")
        filepropselement.setAttribute("statereadmethod", "1")
        filepropselement.setAttribute("statewritemethod", "1")
        return filepropselement        
