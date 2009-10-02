#!/usr/bin/python


#Run this program 
import os
import sys


# metadata
class ioparam:
    name=""
    pid=""
    ptype=""
    size=1
    cols=0
    rows=0
    def __init__(self, iname, iproperty):
        self.name=iname
        self.mproperty=iproperty
