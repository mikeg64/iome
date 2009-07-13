#To use these functions make sure the location of the IOME iogs application
#is on the path
#Linux export IOME_HOME=PATHTOIOME
#Linux export PATH=$PATH":$IOME_HOME/bin"
#Windows set IOME_HOME=PATHTOIOME
#Windows set PATH=%PATH%;$IOME_HOME/bin

#to use the python comands run python IoSetUpGenericPythonSimulation.py

import os

senv_iome_home=str(os.getenv('IOME_HOME'));
apath=senv_iome_home+'\IoGenericSimulation\Debug';
#set the path
path=os.getenv('PATH');
newpath=path+';'+apath;
os.putenv('PATH',newpath);

apythonpath=senv_iome_home+'\IoGenericPythonSimulation';
#set the path
os.getenv('PYTHONPATH');

try:
    newpythonpath=pythonpath+';'+apythonpath;
except :
    newpythonpath=apythonpath;
    
os.putenv('PYTHONPATH',newpythonpath);
import iome
#calls to update xindice database
#import iomexin

