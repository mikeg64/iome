#!/usr/bin/python


#Run this program 
import os
import sys

#from IoSteerWS_client import *
from IoSteerWS_services import *

    
#To use these defs make sure the location of the IOME iogs application
#is on the path
#Linux export IOME_HOME=PATHTOIOME
#Linux export PATH=$PATH":$IOME_HOME/bin"
#Windows set IOME_HOME=PATHTOIOME
#Windows set PATH=%PATH%;$IOME_HOME/bin

#use the following command to mstream data from the system command to the
#python routine
#    res=os.popen(scommand).readlines()
#    property=res[0].strip()  #strip off end of line character assume only one line
#    return property;



def zeros(vsize):
  vec=[]
  b=0
  while b < vsize:
    vec.append(0)
    b=b+1
  return vec

def newmat(nr,nc):
  mat=[]

  ir=0
  ic=0
  while ir < nr:
      vec=[]
      while ic < nc:
            vec.append(0)
            ic=ic+1
      mat.append(vec)
      ic=0
      ir=ir+1
  return mat 


def newmmat3d(nx,ny,nz,nr,nc):
  mmat3d=[]
  ix=0
  iy=0
  iz=0

  while ix < nx:
      v1=[]
      while iy < ny:
          v2=[]
          while iz < nz:
              mat=newmat(nr,nc)
              iz=iz+1
              v2.append(mat)
          v1.append(v2)
          iy=iy+1
          iz=0
      mmat3d.append(v1)
      ix=ix+1
      iy=0

  return mmat3d 

def getmmat3dmat(mmat3d, nx,ny,nz):
  mat=mmat3d[nx][ny][nz]
  return mat

def getmatfloat(mat,ir,ic):
  val=mat[ir][ic]
  return val

def setmmat3dmat(mmat3d, nx,ny,nz,mat):
  mmat3d[nx][ny][nz]=mat
  return mmat3d

def setmatfloat(mat,ir,ic,val):
  mat[ir][ic]=val
  return mat
  

def stringtovec(stringvar, vsize, separator):
  vec=zeros(vsize);
  toks=stringvar.split(separator)
  b=0
  while b < vsize:
    vec[b]=float(toks[b])
    b=b+1
  return vec

def mattovec(mat):
  nr=len(mat);
  nc=len(mat[0]);
  vsize=nr*nc;
  vec=zeros(vsize);

  b=0;
  ic=-1;
  while ic<nc:
    ir=0;
    ic=ic+1;
    while ic<nc and ir<nr:
      vec[b]=mat[ir][ic];
      ir=ir+1
      b=b+1

    

  return vec

def vectomat(vec,nr,nc):
  vsize=len(vec);
  mat=newmat(nr,nc);
   
  b=0;
  ic=-1;
  while ic<nc:
    ir=0;
    ic=ic+1
    while ir<nr and ic<nc:
      mat[ir][ic]=vec[b];
      ir=ir+1
      b=b+1
    
   

  return mat


def vectostring(vec,separator):
  vsize=len(vec);
  vecstring='';
  b=0
  while b < vsize:
    if b>0:
      newvecstring=vecstring+separator+str(vec[b]);
    else:
      newvecstring=str(vec[b]);        
    vecstring=newvecstring;
    b=b+1
  return vecstring
  

def iome(sserver,iport,iid):

    myvar=[]
    myvar.append(sserver)
    myvar.append(iport)
    myvar.append(iid)

    return myvar;




def exitiome(varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = exitiomeRequest();
      request._id=id;
      response=service.exitiome(request);  
      result=response._status;
    except ValueError:
      print "ExitIOME Errot"
      result =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return result;




def addmetadata(name, property,varargin):
#AddMetadata(name, property, port)  
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = addmetadataRequest();
      request._id=id;
      request._property=property;

      response=service.addmetadata(request);
    
      result=response._status;
    except ValueError:
      print "AddMetadata Error"
      result =-1;
      
    return result;

def setmetadata(name, property,varargin):
  #SetMetadata(name, property, port) 
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
   
    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = setmetadataRequest();
      request._id=id;
      request._name=name;
      request._property=property;

      response=service.setmetadata(request);
    
      result=response._status;
    except ValueError:
      print "Set Metadata Error"
      result =-1;
      
    return result;

def getmetadata(name,varargin):
  #GetMetadata(name, property, port) 
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
  
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getmetadataRequest();
      request._id=id;
      request._name=name;

      response=service.getmetadata(request);
    
      result=response._property;
    except ValueError:
      print "Get Metadata error!"
      result =-1;
    
    return result;


def addparamdouble(name, vfloat,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = addparamdoubleRequest();
      request._id=id;
      request._name=name;
      request._value=vfloat;
      request._iflag=flag;

      response=service.addparamdouble(request);
    
      result=response._status;
    except ValueError:
      print "AddFloatParam error!"
      result =-1;

    return result;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()
 

def getparamdouble(name,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #scommand="iogs getparam float "+ name+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #fval=float(res[0].strip())
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getparamdoubleRequest();
      request._id=id;
      request._name=name;

      response=service.getparamdouble(request);
    
      fval=response._value;
    except ValueError:
      print "GetFloatParam error!"
      fval =-1;

    
    
    return fval;


def setparamdouble(name, vfloat,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #scommand="iogs setparam float "+ name+" "+str(vfloat)+" "+str(flag)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #fval=(res[0].strip())
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = setparamdoubleRequest();
      request._id=id;
      request._name=name;
      request._value=vfloat;

      response=service.setparamdouble(request);
    
      result=response._status;
    except ValueError:
      print "SetFloatParam error!"
      result =-1;    
    return result;



def addparamint(name, var,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    #scommand="iogs addparam int "+name+ " "+ str(var)+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = addparamintRequest();
      request._id=id;
      request._name=name;
      request._value=var;
      request._iflag=flag;

      response=service.addparamint(request);
    
      result=response._status;
    except ValueError:
      print "AddIntParam error!"
      result =-1;    
    
    return result;


def getparamint(name,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
    
    #scommand="iogs getparam int "+ name+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #ival=int(res[0].strip())

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getparamintRequest();
      request._id=id;
      request._name=name;

      response=service.getparamint(request);
    
      ival=response._value;
    except ValueError:
      print "GetIntParam error!"
      ival =-1;    
    
    return ival;

def setparamint(name, var,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #scommand="iogs setparam int "+ name+" "+str(var)+" "+str(flag)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #ival=(res[0].strip())
    try:
      scontact="http://"+server+":"+str(port);
      service=IoSteerWSSOAP(url=scontact);
      request = setparamintRequest();
      request._id=id;
      request._name=name;
      request._value=var;

      response=service.setparamint(request);
    
      result=response._status;
    except ValueError:
      print "SetIntParam error!"
      result =-1;    
    
    return result;


def addparamstring(name, var,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    port=8080;
    flag=7;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #scommand="iogs addparam string "+name+ " "+ var+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = addparamstringRequest();
      request._id=id;
      request._name=name;
      request._value=var;
      request._iflag=flag;

      response=service.addparamstring(request);
    
      result=response._status;
    except ValueError:
      print "AddStringParam error!"
      result =-1;    
    
    return result;


def getparamstring(name,varargin):
  #AddMetadata(name, property, port)
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #scommand="iogs getparam float "+ name+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #fval=float(res[0].strip())
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getparamstringRequest();
      request._id=id;
      request._name=name;

      response=service.getparamstring(request);
    
      fval=response._value;
    except ValueError:
      print "GetStringParam error!"
      fval =-1;

    
    
    return fval;

    





def setparamstring(name, var,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    #scommand="iogs setparam string "+ name+" "+var+" "+str(flag)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = setparamstringRequest();
      request._id=id;
      request._name=name;
      request._value=var;

      response=service.setparamstring(request);
    
      result=response._status;
    except ValueError:
      print "SetStringParam error!"
      result =-1;    
    
    return result;

def addparamvec(name, var, vsize,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #vecstring=vectostring(var, vecsize,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #uvecstring=sprintf('""%s""',vecstring); 
  #scommand=sprintf("iogs addparam vec %s %s %d %d %s", name, uvecstring,vsize,flag,  port,server);
    
    #scommand="iogs addparam vec "+name+ " "+ vecstring+" "+str(vsize)+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()
    scontact="http://"+server+":"+str(port);
    #vvar=urn_IoSteerWS.ArrayOfdouble_(var,vsize)
    try:
      service=IoSteerWSSOAP(url=scontact);

      
      request = addparamvecRequest();
      request._id=id;
      request._name=name;
      request._value=var;
      request._iflag=flag;
      request._n=vsize;

      response=service.addparamvec(request);
    
      result=response._status;
      ##vecstring=vectostring(var,",");
      ##scommand="iogs addparam vec "+name+ " "+ vecstring+" "+str(vsize)+" "+str(flag)+" "+str(id)+" "+str(port)+" "+server;
      ##res=os.popen(scommand).readlines()
      ##result=res
      
    except ValueError:
      print "AddVecParam error!"
      result =-1;    
    
    return result;



def getparamvec(name, vecsize,varargin):
  #AddMetadata(name, property, port)  
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
    #scommand="iogs getparam vec "+ name+" "+str(vecsize)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()
    #vec=stringtovec(result, vecsize,',');

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getparamvecRequest();
      request._id=id;
      request._name=name;
      request._n=vecsize;

      response=service.getparamvec(request);
    
      val=response._dval;
    except ValueError:
      print "GetVecParam error!"
      val =-1;    
    
    return val;
  


def setparamvec(name, vec, vecsize,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
    
    #vecstring=vectostring(vec, vecsize,',');  
    #put double quotes around the vec string so that it is
    #passed into unix shell script as a single variable
    #uvecstring=sprintf('""%s""',vecstring);
    #scommand=sprintf("iogs setparam vec %s %s %d %s", name, uvecstring,vecsize,flag,  port,server);
    #result=os.system(scommand);
    #status=0;
    #scommand="iogs setparam vec "+ name+" "+vecstring+" "+str(vecsize)+" "+str(flag)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #result=(res[0].strip())
    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = setparamvecRequest();
      request._id=id;
      request._name=name;
      request._value=vec;
      
      request._n=vecsize;

      response=service.setparamvec(request);
    
      result=response._status;
    except ValueError:
      print "SetVecParam error!"
      result =-1;     
    return result;




def addparammat(name, var,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    port=8080;
    flag=7;
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
    nr=len(var);
    nc=len(var [0]);
    vvar=mattovec(var);
    #i=0
    #j=0
    #vvar=[]
    #while i<nr:
    #  j=0
    #  while j<nc:
    #     vvar.append(var[i][j]);
    #     j=j+1
    #  i=i+1
      
    #matstring=vectostring(vvar, nr,nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #umatstring=sprintf('""%s""',matstring); 
  #scommand=sprintf("iogs addparam mat %s %s %d %d %d %s", name, umatstring,nr,nc,flag,  port,server);
  #result=os.system(scommand);
  #status=0;

    #scommand="iogs addparam mat "+name+ " "+ matstring+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = addparammatRequest();
      request._id=id;
      request._name=name;
      request._value=vvar;
      request._iflag=flag;
      request._nr=nr;
      request._nc=nc;

      response=service.addparammat(request);
    
      result=response._status;
    except ValueError:
      print "AddMatParam error!"
      result =-1;    
    return result;



def getparammat(name, nr,nc,varargin):
  #AddMetadata(name, property, port)
  
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
  
    #scommand=sprintf("iogs getparam mat %s %s %d %d %s", name, float,nr,nc,  port,server);
    #result=os.system(scommand);
    #tmat=stringtovec(result, nr*nc,',');
    #scommand="iogs getparam mat "+ name+" "+str(nr)+" "+str(nc)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()
    #vecsize=nr*nc
    #tmat=stringtovec(result, vecsize,',');
      


    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getparammatRequest();
      request._id=id;
      request._name=name;
      request._nr=nr;
      request._nc=nc;

      response=service.getparammat(request);
    
      result=response._dval;
    except ValueError:
      print "GetMatParam error!"
      result =-1;    

    mat=vectomat(result,nr,nc);
    return mat;



def setparammat(name, var,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    nr=len(var);
    nc=len(var[0]);
    vvar=mattovec(var);
    #put double quotes around the vec string so that it is
    #passed into unix shell script as a single variable
    #umatstring=sprintf('""%s""',matstring); 
    #scommand=sprintf("iogs addparam mat %s %s %d %d %d %s", name, umatstring,nr,nc,flag,  port,server);
    #result=os.system(scommand);
    #status=0;

    #scommand="iogs setparam mat "+name+ " "+ matstring+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = setparammatRequest();
      request._id=id;
      request._name=name;
      request._value=vvar;
      request._iflag=flag;
      request._nr=nr;
      request._nc=nc;

      response=service.setparammat(request);
    
      result=response._status;
    except ValueError:
      print "SetMatParam error!"
      result =-1;    
    
    return result;









def addparammmat3d(name, var, ni,nj,nk,nr,nc,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  

  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #umatstring=sprintf('""%s""',matstring); 
  #scommand=sprintf("iogs addparam mat %s %s  %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  port,server);
  #result=os.system(scommand);
  #status=0;

    #scommand="iogs addparam mmat3d "+name+ " "+ mm3dstring+" "+str(ni)+" "+str(nj)+" "+str(nk)+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = addparammat3dRequest();
      request._id=id;
      request._name=name;
      request._value=var;
      request._iflag=flag;
      request._nr=nr;
      request._nc=nc;
      request._n=ni;
      request._p=nj;
      request._q=nk;

      response=service.addparammat3d(request);
    
      result=response._status;
    except ValueError:
      print "Addmmat3dParam error!"
      result =-1;    
    
    return result;



def getparammmat3d(name, ni,nj,nk,nr,nc,varargin):
  #AddMetadata(name, property, port)
  
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
  
  #scommand=sprintf("iogs getparam mat %s %s %d %d %d %d %d %d %s", name, mm3d,n,nj,nk,nr,nc,  port,server);
  #result=os.system(scommand);
  #tmat=stringtovec(result, ni*nj*nk*nr*nc,',');
    #scommand="iogs getparam mmat3d "+ name+" "+" "+str(ni)+" "+str(nj)+" "+str(nk)+" "+str(nr)+" "+str(nc)+" "+str(port)+" "+server
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()
    

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getparammat3dRequest();
      request._id=id;
      request._name=name;
      request._nr=nr;
      request._nc=nc;
      request._n=ni;
      request._p=nj;
      request._q=nk;

      response=service.getparammat3d(request);
    
      result=response._mmat3d;
    except ValueError:
      print "Getmmat3dParam error!"
      result =-1;    
    
    return result;


def setparammmat3d(name, var, ni,nj,nk,nr,nc,varargin):
  #AddMetadata(name, property, port) 
    flag=7;
    nargin=len(varargin);
    port=8080;

    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;
  
  
    #put double quotes around the vec string so that it is
    #passed into unix shell script as a single variable
    #umatstring=sprintf('""%s""',matstring); 
    #scommand=sprintf("iogs addparam mat %s %s  %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  port,server);
    #result=os.system(scommand);
    #status=0;

    #scommand="iogs setparam mmat3d "+name+ " "+ mm3dstring+" "+str(ni)+" "+str(nj)+" "+str(nk)+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    #res=os.popen(scommand).readlines()
    #result=res[0].strip()

    scontact="http://"+server+":"+str(port);
    try:
      service=IoSteerWSSOAP(url=scontact);
      request = setparammat3dRequest();
      request._id=id;
      request._name=name;
      request._value=var;
      request._iflag=flag;
      request._nr=nr;
      request._nc=nc;
      request._n=ni;
      request._p=nj;
      request._q=nk;

      response=service.setparammat3d(request);
    
      result=response._status;
    except ValueError:
      print "Setmmat3dParam error!"
      result =-1;    
    
    return result;

def runsimulation(simfile, outfile, varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = runsimulationRequest();


      #read simulation file
      
      request._id=id;

      f=open(simfile,'r');
      scontent=f.read();
      request._simfilecontent=scontent;
      f.close();
      
      response=service.runsimulation(request);
  
      result=response._result;
      f=open(outfile,'w');
      f.write(result);
      f.close();
      
    except ValueError:
      print "RunSimulation Errot"
      result =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return result;

def requestsimulation(simfile, varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = requestsimulationRequest();


      #read simulation file
      
      
      if simfile !="null":
          f=open(simfile,'r');
          scontent=f.read();
          f.close();
      else:
          scontent='null';
      request._simfilecontent=scontent;
        
        
      
      response=service.requestsimulation(request);
  
      newid=response._isimid;
      f=open(outfile,'w');
      f.write(result);
      f.close();
      
    except ValueError:
      print "RequestSimulation Errot"
      newid =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return newid;

    
def submitsimulation(simfile, varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = submitsimulationRequest();


      #read simulation file
      
      request._id=id;

      f=open(simfile,'r');
      scontent=f.read();
      request._simfilecontent=scontent;
      f.close();
      
      response=service.submitsimulation(request);
  
      isimid=response._isimid;
      
    except ValueError:
      print "SubmitSimulation Error"
      isimid =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return isimid;

def simulationstatus(varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = simulationstatusRequest();


      #read simulation file
      
      request._isimid=id;

      
      response=service.simulationstatus(request);
  
      status=response._status;
      
    except ValueError:
      print "SimulationStatus Error"
      status =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return status;


def getsimulationresult(outfile, varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getsimulationresultRequest();


      #read simulation file
      
      request._isimid=id;

      response=service.getsimulationresult(request);
  
      result=response._result;
      f=open(outfile,'w');
      f.write(result);
      f.close();
      
    except ValueError:
      print "GetSimulationResult Errot"
      result =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return result;

def deletesimulation(varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = deletesimulationRequest();


      #read simulation file
      
      request._isimid=id;

      
      response=service.deletesimulation(request);
  
      status=response._status;
      
    except ValueError:
      print "DeleteSimulation Error"
      status =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return status;

def readsimulation(simfile,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = readsimulationRequest();


      #read simulation file
      
      request._isimid=id;
      request._filename=simfile;

      
      response=service.readsimulation(request);
  
      status=response._status;
      
    except ValueError:
      print "ReadSimulation Error"
      status =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return status;

def readlocalsimulation(simfile,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = readlocalsimulationRequest();


      #read simulation file
      
      request._isimid=id;
      request._filename=simfile;

      
      response=service.readlocalsimulation(request);
  
      status=response._status;
      
    except ValueError:
      print "ReadLocalSimulation Error"
      status =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return status;



def newsimulation(simname,xslname,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = newsimulationRequest();


      #read simulation file
      
      request._id=id;
      request._simname=simname;
      request._xslname=xslname;

      
      response=service.newsimulation(request);
  
      status=response._status;
      
    except ValueError:
      print "NewSimulation Error"
      status =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return status;


def writesimulation(simfile,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = writesimulationRequest();


      #read simulation file
      
      request._id=id;
      request._filename=simfile;


      
      response=service.writesimulation(request);
      result=response._filecontent;
      f=open(simfile,'w');
      f.write(result);
      f.close();
      
    except ValueError:
      print "WriteSimulation Error"
      result =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return result;

def writelocalsimulation(simfile,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = writelocalsimulationRequest();


      #read simulation file
      
      request._id=id;
      request._filename=simfile;


      
      response=service.writelocalsimulation(request);
      result=response._filecontent;
      f=open(simfile,'w');
      f.write(result);
      f.close();
      
    except ValueError:
      print "WriteLocalSimulation Error"
      result =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return result;



def getobjnum(varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getobjnumRequest();


      #read simulation file
      
      request._id=id;

      
      response=service.getobjnum(request);
  
      objnum=response._objnum;
      
    except ValueError:
      print "GetObjNum Error"
      objnum =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return objnum;


def getnumobj(varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getnumobjRequest();


      #read simulation file
      
      request._id=id;

      
      response=service.getnumobj(request);
  
      numobj=response._numobj;
      
    except ValueError:
      print "GetNumObj Error"
      numobj =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return numobj;


def groupbarrier(myid, varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    #try:
    #  scommand="iogs groupbarrier "+str(id)+" "+str(port)+" "+server;
    #  result=os.system(scommand);
    #except ValueError:
    #  print "GroupBarrier Error"
    #  result =-1;


    try:
      service=IoSteerWSSOAP(url=scontact);
      request = getnumobjRequest();
      request._id=id;
      response=service.getnumobj(request);
      numobj=response._numobj;
      testnotcomplete=1;
      if numobj>1:
        iprocstate=zeros(numobj);
        request = setgroupbarrierRequest();
        request._id=id;
        request._state=1;
        response=service.setgroupbarrier(request);
        while testnotcomplete==1:
          i=0;
          while i<numobj:
            if iprocstate[i]==0:
              request = testgroupbarrierRequest();
              request._id=id;
              response=service.testgroupbarrier(request);
              state=response._state;
              if state == 0:
                testnotcomplete=1;
              else:
                testnotcomplete=0;
            i=i+1;
            
        request = setgroupbarrierRequest();
        request._id=id;
        request._state=1;
        response=service.setgroupbarrier(request);             
        
    except ValueError:
      print "GroupBarrier Error"
      result =-1;
    

    return result;

def deleteparam(paramname,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = deleteparamRequest();


      #read simulation file
      request._name=paramname;    
      request._id=id;

      
      response=service.deleteparam(request);
  
      status=response._status;
      
    except ValueError:
      print "DeleteParam Error"
      status =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return status;

def listparam(paramtype,varargin):
  #Stop the server and exit IOME
    port=8080;
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>2:
            port=varargin[1];
            id=varargin[2];
        else:
            id=0;
            if nargin>1:
              port=varargin[2]
    else:
        server='localhost';
        port=8080;
        id=0;

    scontact="http://"+server+":"+str(port);

    try:
      service=IoSteerWSSOAP(url=scontact);
      request = listparamRequest();


      #read simulation file
      request._type=paramtype;    
      request._id=id;

      
      response=service.listparam(request);
  
      slist=response._list;
      
    except ValueError:
      print "ListParam Error"
      slist =-1;
  
  #scommand="iogs exitiome";
  #result=os.system(scommand);
    return slist;
