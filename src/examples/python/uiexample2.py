#!/usr/bin/python

import os
from Tkinter import *
import tkFileDialog
import iome
import iomepar
import tkSimpleDialog

myiomepar=iomepar.iomepar('null','mysim','null',8080,'localhost',10,1,1,1,0)


def ConnectionWindow() :
    #win = Toplevel()
    b = ConnectionDialog(root)


class steeringparams:
    """A simple example class"""
    i = 12345
    def f(self):
        return 'running iome'

    def __init__(self, wavenumber, maxamplitude, frequency):
        self.elist=iome.iome('localhost',8080,0);
        self.wavenumber = wavenumber
        self.maxamplitude = maxamplitude
        self.frequency = frequency
        self.steeringenabled = 0
        self.finishsteering = 0
        
    def getparams(self):
        self.maxamplitude = iome.getparamdouble('maxamplitude',self.elist);
        self.frequency = iome.getparamdouble('wavefreq',self.elist);
        #self.steerinenabled = iome.getparamint('steeringenabled',self.elist);
        #self.finishsteering = iome.getparamint('finishsteering',self.elist);
        self.wavenumber = iome.getparamvec('wavenumber',2,self.elist);

    def setparams(self):
        iome.setparamdouble('maxamplitude',self.maxamplitude,self.elist);
        iome.setparamdouble('wavefreq', self.frequency, self.elist);
        #iome.setparamint('steeringenabled', self.steerinenabled, self.elist);
        #iome.setparamint('finishsteering', self.finishsteering, self.elist);
        iome.setparamvec('wavenumber',self.wavenumber, 2,self.elist);


class ConnectionDialog(tkSimpleDialog.Dialog):

    def body(self, master):

        Label(master, text="server:").grid(row=0)
        Label(master, text="port:").grid(row=1)
        Label(master, text="id:").grid(row=2)
        self.e1 = Entry(master)
        self.e2 = Entry(master)
        self.e3 = Entry(master)
        
        self.e1.insert(0,"localhost");
        self.e2.insert(0,"8080");
        self.e3.insert(0,"0");
        
        self.e1.grid(row=0, column=1)
        self.e2.grid(row=1, column=1)
        self.e3.grid(row=2, column=1)
        return self.e1 # initial focus

    def apply(self):
        server = (self.e1.get())
        port = (self.e2.get())
        id=(self.e3.get())
        if len(server)>0:
            myiomepar.hostname=server
        if len(id)>0:
            myiomepar.procid=id
        if len(port)>0:    
            myiomepar.port=port
        print myiomepar.hostname, myiomepar.procid, myiomepar.port # or something


class Application(Frame):
    def setparams(self):
        #this will de the actual set params
        print "set params!"
        self.mysteeringparams.setparams();

    def getparams(self):
        #this will de the actual set params
        print "get params!"
        self.mysteeringparams.getparams();
        self.e1.insert(0,self.mysteeringparams.maxamplitude);
        self.e2.insert(0,self.mysteeringparams.wavenumber[0]);
        self.e3.insert(0,self.mysteeringparams.wavenumber[1]);
        self.e4.insert(0,self.mysteeringparams.frequency);        


    def connection(self):
        #this will de the actual set params
        ConnectionWindow()
        print "messagewinf!"
        self.mysteeringparams.elist=iome.iome(myiomepar.hostname,myiomepar.port,myiomepar.procid);
        
    def maxamplitude(self, event):
        #this will de the actual set params
        self.mysteeringparams.maxamplitude=float(self.e1.get());
        iome.setparamdouble('maxamplitude', self.mysteeringparams.maxamplitude, self.mysteeringparams.elist);
        print "maxamplitude!"

    def frequency(self, event):
        self.mysteeringparams.frequency=float(self.e4.get());
        #this will de the actual set params
        iome.setparamdouble('wavefreq', self.mysteeringparams.frequency, self.mysteeringparams.elist);
        print "frequency!"

    def k1(self, event):
        #this will de the actual set params
        self.mysteeringparams.wavenumber[0]=float(self.e2.get());
        iome.setparamvec('wavenumber', self.mysteeringparams.wavenumber,2, self.mysteeringparams.elist);
        print "k1!"

    def k2(self, event):
        #this will de the actual set params
        self.mysteeringparams.wavenumber[1]=float(self.e3.get());
        iome.setparamvec('wavenumber', self.mysteeringparams.wavenumber,2, self.mysteeringparams.elist);
        
        print "k2!"
 

    def enablesteering(self):
        #this will de the actual set params
        print "enablesteering!"
        es=self.mysteeringparams.steeringenabled
        if es==1:
            self.mysteeringparams.steeringenabled=0
        else:
            self.mysteeringparams.steeringenabled=1
        print self.mysteeringparams.steeringenabled
        iome.setparamint('steeringenabled', self.mysteeringparams.steeringenabled, self.mysteeringparams.elist);
            

    def finishsteering(self):
        #this will de the actual set params
        print "finishsteering"
        es=self.mysteeringparams.finishsteering
        if es==1:
            self.mysteeringparams.finishsteering=0
        else:
            self.mysteeringparams.finishsteering=1
        iome.setparamint('finishsteering', self.mysteeringparams.finishsteering, self.mysteeringparams.elist);


    def createWidgets(self):


        self.l1=Label(self, text="maxamlitude:")
        self.l2=Label(self, text="wavenumer k1:")
        self.l3=Label(self, text="wavenumer k2:")
        self.l4=Label(self, text="frequency:")
        self.b1=Button(self, text="enable steering:")
        self.b1["command"] =  self.enablesteering

        self.b2=Button(self, text="finish steering:")
        self.b2["command"] =  self.finishsteering



        self.l1.grid(row=0)
        self.l2.grid(row=1)
        self.l3.grid(row=2)
        self.l4.grid(row=3)
        self.b1.grid(row=4,column=1)
        self.b2.grid(row=4,column=2)


        self.e1 = Entry(self)
        self.e2 = Entry(self)
        self.e3 = Entry(self)
        self.e4 = Entry(self)
        
        self.e1.insert(0,"20");
        self.e2.insert(0,"10");
        self.e3.insert(0,"5");
        self.e4.insert(0,"8");

        self.e1.bind('<Key-Return>',self.maxamplitude)
        self.e2.bind('<Key-Return>',self.k1)
        self.e3.bind('<Key-Return>',self.k2)
        self.e4.bind('<Key-Return>',self.frequency)
        
        self.e1.grid(row=0, column=1)
        self.e2.grid(row=1, column=1)
        self.e3.grid(row=2, column=1)
        self.e4.grid(row=3, column=1)

        self.connect = Button(self)
        self.connect["text"] = "connection"
        self.connect["command"] =  self.connection
        self.connect.grid(row=5)



        self.QUIT = Button(self)
        self.QUIT["text"] = "QUIT"
        self.QUIT["fg"]   = "red"
        self.QUIT["command"] =  self.quit
        self.QUIT.grid(row=5,column=1)

        self.setp = Button(self)
        self.setp["text"] = "set params",
        self.setp["command"] = self.setparams
        self.setp.grid(row=5,column=3)

        self.getp = Button(self)
        self.getp["text"] = "get params",
        self.getp["command"] = self.getparams
        self.getp.grid(row=5,column=4)



    def __init__(self, master=None):
        Frame.__init__(self, master)
        k=iome.zeros(2);
        k[0]=10;
        k[1]=5;
        self.mysteeringparams=steeringparams(k,20,8);
        self.pack()
        self.createWidgets()


root = Tk()
app = Application(master=root)
app.master.title("Steering Example")
app.master.maxsize(1000, 400)
app.mainloop()
root.destroy()
