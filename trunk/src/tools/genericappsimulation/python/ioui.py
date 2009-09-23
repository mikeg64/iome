#!/usr/bin/python
# File: menu1.py

import os
from Tkinter import *
import tkFileDialog

import iomepar
import tkSimpleDialog

myiomepar=iomepar.iomepar('null','mysim','null',8080,'localhost',10,1,1,1,0)

root = Tk()


class MyDialog(tkSimpleDialog.Dialog):

    def body(self, master):

        Label(master, text="Simname:").grid(row=0)
        Label(master, text="Script Name:").grid(row=1)
        Label(master, text="Port:").grid(row=2)
        self.e1 = Entry(master)
        self.e2 = Entry(master)
        self.e3 = Entry(master)
        
        self.e1.grid(row=0, column=1)
        self.e2.grid(row=1, column=1)
        self.e3.grid(row=2, column=1)
        return self.e1 # initial focus

    def apply(self):
        ssimname = (self.e1.get())
        sscriptname = (self.e2.get())
        sport=(self.e3.get())

        if len(ssimname)>0:
            myiomepar.simname=ssimname
        if len(sscriptname)>0:
            myiomepar.scriptname=sscriptname
        if len(sport)>0:    
            myiomepar.port=sport
        print myiomepar.simname, myiomepar.scriptname, myiomepar.port # or something



def messageWindow() :
    #win = Toplevel()
    b = MyDialog(root)

def ioexit():
    sys.exit();

def initiome():
    myiomepar.initiome();

def callback():
    print "called the callback!"

def iodir():
    directory=tkFileDialog.askdirectory()
    print directory
    os.chdir(directory)

def ionew():
    myfile=tkFileDialog.asksaveasfile()
    print myfile
    
def ioopen():
    myfile=tkFileDialog.askopenfile()
    print myfile

def initiomedialog():
    messageWindow()

def about():
    print "a simple gui for iome"


# create a menu
#menu = Menu(root, borderwidth=150)
menu=Menu(root)
root.config(menu=menu, height=150, width=300)

filemenu = Menu(menu)
menu.add_cascade(label="File", menu=filemenu)
filemenu.add_command(label="New", command=ionew)
filemenu.add_command(label="Open...", command=ioopen)
filemenu.add_command(label="Directory...", command=iodir)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=ioexit)

exemenu = Menu(menu)
menu.add_cascade(label="Exe", menu=exemenu)
exemenu.add_command(label="Init...", command=initiome)
exemenu.add_command(label="Params...", command=initiomedialog)

helpmenu = Menu(menu)
menu.add_cascade(label="Help", menu=helpmenu)
helpmenu.add_command(label="About...", command=about)

root.mainloop()
#top = Toplevel(height=300, width=600)

