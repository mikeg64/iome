#!/usr/bin/python
# File: menu1.py

from Tkinter import *
import iomepar
import tkSimpleDialog

myiomepar=iomepar.iomepar('null','mysim','null',8080,'localhost',10,1,1,1,0)

root = Tk()


class MyDialog(tkSimpleDialog.Dialog):

    def body(self, master):

        Label(master, text="Simname:").grid(row=0)
        Label(master, text="Script Name:").grid(row=1)

        self.e1 = Entry(master)
        self.e2 = Entry(master)

        self.e1.grid(row=0, column=1)
        self.e2.grid(row=1, column=1)
        return self.e1 # initial focus

    def apply(self):
        first = (self.e1.get())
        second = (self.e2.get())
        myiomepar.simname=first
        myiomepar.scriptname=second
        print first, second # or something



def messageWindow() :
    #win = Toplevel()
    b = MyDialog(root)



def initiome():
    myiomepar.initiome();

def callback():
    print "called the callback!"

def initiomedialog():
    messageWindow()




# create a menu
menu = Menu(root)
root.config(menu=menu)

filemenu = Menu(menu)
menu.add_cascade(label="File", menu=filemenu)
filemenu.add_command(label="New", command=callback)
filemenu.add_command(label="Open...", command=callback)
filemenu.add_command(label="Directory...", command=callback)
filemenu.add_separator()
filemenu.add_command(label="Exit", command=exit)

exemenu = Menu(menu)
menu.add_cascade(label="Exe", menu=exemenu)
exemenu.add_command(label="Init...", command=initiome)
exemenu.add_command(label="Params...", command=initiomedialog)

helpmenu = Menu(menu)
menu.add_cascade(label="Help", menu=helpmenu)
helpmenu.add_command(label="About...", command=callback)

root.mainloop()
top = Toplevel()

