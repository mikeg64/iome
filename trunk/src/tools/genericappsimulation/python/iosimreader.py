#!/usr/bin/python


#Run this program 
import os
import sys
import xml.sax.handler
from iometadata import *
from iogenericsimulation import *
from iosimwriter import *


# simreader
class simhandler(xml.sax.handler.ContentHandler):
    simulation=""
    currentprop=""
    numprops=0
    def __init__(self, isim):
        self.simulation=isim
    def startElement(self, name, attributes):
        if name == "props":
            self.numprops = attributes["numprops"]
        elif name == "prop":
            self.buffer = ""
            pname=attributes["name"]
            pindex=attributes["index"]
            self.currentprop = ioparam(pname)
        elif name == "metadata":
            psim=self.simulation
            psim.addmetadata(attributes["name"],attributes["property"])
        elif name == "int":
            psim=self.simulation
            pprop=self.currentprop
            pprop.type="int"
            psim.addprop(self.currentprop)
        elif name == "float":
            self.inTitle = 1
        elif name == "string":
            self.inTitle = 1
        elif name == "vec":
            self.inTitle = 1
        elif name == "mat":
            self.inTitle = 1
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


