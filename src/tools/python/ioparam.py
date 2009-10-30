#!/usr/bin/python


#Run this program 
import os
import sys


# metadata
class ioparam:

    def __init__(self, iname, iproperty):
        self.name=iname
        self.mproperty=iproperty
        self.ptype="int"
        self.pid=""
        self.ptype=""
        self.size=1
        self.cols=0
        self.rows=0
        self.svalue=""
