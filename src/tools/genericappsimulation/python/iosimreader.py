#!/usr/bin/python


#Run this program 
import os
import sys
import xml.sax.handler
from iometadata import *
from iogenericsimulation import *
from iosimwriter import *
from ioparam import *

# simreader
class simhandler(xml.sax.handler.ContentHandler):
    simulation=""
    currentprop=""
    numprops=0
    currentindex=0
    def __init__(self, isim):
        self.simulation=isim
    def startElement(self, name, attributes):
        if name == "props":
            self.numprops = attributes["numprops"]            
            #create an array of props
            for n in range(1, self.numprops):
                iparam=ioparam("prop","value")
                self.simulation.addprop(iparam)
        elif name == "prop":
            self.buffer = ""
            pname=attributes["name"]
            pindex=attributes["index"]
            self.currentprop = self.simulation.getprop(pindex)
            self.currentindex=pindex
            self.currentprop.name=pname
        elif name == "metadata":
            psim=self.simulation
            psim.addmetadata(attributes["name"],attributes["property"])
        elif name == "int":
            psim=self.simulation
            pprop=self.currentprop
            pprop.type="int"
            pprop.svalue=self.buffer
            psim.setprop(self.currentindex,self.currentprop)
        elif name == "float":
            psim=self.simulation
            pprop=self.currentprop
            pprop.type="float"
            pprop.svalue=self.buffer
            psim.setprop(self.currentindex,self.currentprop)
        elif name == "string":
            psim=self.simulation
            pprop=self.currentprop
            pprop.type="string"
            pprop.svalue=self.buffer
            psim.setprop(self.currentindex,self.currentprop)
        elif name == "vec":
            psim=self.simulation
            pprop=self.currentprop
            pprop.type="vec"
            pprop.size=attributes["size"]
            pprop.svalue=self.buffer
            psim.setprop(self.currentindex,self.currentprop)
        elif name == "mat":
            psim=self.simulation
            pprop=self.currentprop
            pprop.type="mat"
            pprop.rows=attributes["rows"]
            pprop.cols=attributes["cols"]
            pprop.svalue=self.buffer
            psim.setprop(self.currentindex,self.currentprop)
        elif name == "simulation":
            psim=self.simulation
            psim.name=attributes["name"]
    def characters(self, data):
        self.buffer= data
    def endElement(self, name):
        if name == "int":
            pprop=self.currentprop
            pprop.value=data
        elif name == "float":
            pprop=self.currentprop
            pprop.value=data
            self.inTitle = 1
        elif name == "string":
            self.inTitle = 1
            pprop=self.currentprop
            pprop.value=data
        elif name == "vec":
            self.inTitle = 1
            pprop=self.currentprop
            pprop.value=data
        elif name == "mat":
            self.inTitle = 1
            pprop=self.currentprop
            pprop.value=data


