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
    name=""
    metadata=[]
    params=[]
    def __init__(self, iname):
        self.name=iname
    def addmetadata(self, prop,name):
        metad=iometadata(prop,name)
        self.metadata.append(metad)
    def addprop(self, prop):
        self.params.append(prop)
    def readsimulation(self,filename):
        parser = xml.sax.make_parser()
        handler = iosimreader.simhandler()
        parser.setContentHandler(handler)
        parser.parse(filename)
    def writesimulation(self,filename):
        writer=iosimwriter(self)
        status=writer.writesimulation(filename)
	return status

