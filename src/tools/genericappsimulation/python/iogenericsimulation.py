#!/usr/bin/python


#Run this program 
import os
import sys
import xml.sax
from iometadata import *
from iosimreader import *
from iosimwriter import *


# genericsimulation
class iogenericsimulation:

    def __init__(self, iname):
        self.name=iname
        self.metadata=[]
        self.params=[]
    def addmetadata(self, prop,name):
        metad=iometadata(prop,name)
        self.metadata.append(metad)
    def addprop(self, prop):
        self.params.append(prop)
    def getprop(self, index):
        numprops=self.params.len()
        if index<numprops:
            prop=self.params[index]
        else:
            prop=self.params[0]
        return prop
    def setprop(self, index, prop):
        numprops=self.params.len()
        if index<numprops:
            params[index]=prop
        else:
            params[0]=prop
    def readsimulation(self,filename):
        parser = xml.sax.make_parser()
        handler = iosimreader.simhandler()
        parser.setContentHandler(handler)
        parser.parse(filename)
    def writesimulation(self,filename):
        writer=iosimwriter(self)
        status=writer.writesimulation(filename)
	return status

