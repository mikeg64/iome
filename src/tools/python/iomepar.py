#a python class to hold parameters for running iome
#to initialise type


#//char *scriptname, char *simname, char *simxslfile,
#int port , char *hostname="localhost", int maxsims=10, int numtasks=1,int numsubprocs=1, int numprocs=1, int procid=0

#import iome
import Tkinter, subprocess, os, tkSimpleDialog

class iomepar:
    """A simple example class"""
    i = 12345
    def f(self):
        return 'running iome'

    def __init__(self,sscriptname, ssimname, ssimxsl, iport, shostname, imaxsims, inumtasks, inumsubprocs, inumprocs, iprocid ):
        self.scriptname = sscriptname
        self.simname = ssimname
        self.simxsl = ssimxsl
        self.port = iport
        self.hostname = shostname
        self.maxsims = imaxsims
        self.numtasks = inumtasks
        self.numsubprocs = inumsubprocs
        self.numprocs = inumprocs
        self.procid = iprocid
        

    def initiome(self):
        #class to initiome
        #construct command line
        scom1="iogs initiome "+self.scriptname+" "+self.simname+" "+self.simxsl+" "+str(self.port)+" "+self.hostname;
        scom2=" "+str(self.maxsims)+" "+str(self.numtasks)+" "+str(self.numsubprocs)+" "+str(self.numprocs)+" "+str(self.procid);
        scommand=scom1 + scom2;
        print scommand
        subprocess.Popen(scommand, shell=True)
        #os.system(scommand)


