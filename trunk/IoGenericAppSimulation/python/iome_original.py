#!/usr/bin/python


#Run this program 
import os


    
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


def vectostring(vec,separator):
  vsize=len(vec);
  vecstring='';
  b=0
  while b < vsize:
    if b>0:
      newvecstring=vecstring+separator+vec[b];
    else:
      newvecstring=vec[b];        
    vecstring=newvecstring;
  return vectostring
  


def InitIOME(simname, configname, statename, varargin):
#def [status]=InitIOME(simname, configname, statename,port,server)
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;


    #Start the generic simulation
    #Simulation name
    #Config name
    #State file name
    #port
    scommand="iogs startiome "+simname+" "+configname+" "+statename+" "+str(port)+" "+server;
    result=os.system(scommand);
    return result;


def ExitIOME():
  #Stop the server and exit IOME
  scommand="iogs exitiome";
  result=os.system(scommand);
  return result;




def AddMetadata(name, property,varargin):
#AddMetadata(name, property, port)  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
            port=varargin[1];
        else:
            port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs addmetadata "+name+" "+ str(property)+" "+str(port)+" "+server;
    result=os.system(scommand);
    return result;

def SetMetadata(name, property,varargin):
  #SetMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
   
    scommand="iogs addmetadata "+name+" "+str(property)+" "+str(port)+" "+server;
    result=os.system(scommand);
    return result;


def GetMetadata(name,varargin):
  #GetMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
  
    scommand="iogs getmetadata "+name+" "+str(port)+" "+server;
    #property=os.system(scommand);
    res=os.popen(scommand).readlines()
    property=res[0].strip()
    return property;


def AddFloatParam(name, vfloat, flag,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs addparam float "+name+ " "+ str(vfloat)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;


def GetFloatParam(name,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs getparam float "+ name+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    fval=float(res[0].strip())
    return fval;


def SetFloatParam(name, vfloat, flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs setparam float "+ name+" "+str(vfloat)+" "+str(flag)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    fval=(res[0].strip())
    return fval;



def AddIntParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;

    scommand="iogs addparam int "+name+ " "+ str(var)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;


def GetIntParam(name,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
    
    scommand="iogs getparam int "+ name+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    ival=int(res[0].strip())
    return ival;

def SetIntParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs setparam int "+ name+" "+str(var)+" "+str(flag)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    ival=(res[0].strip())
    return ival;


def AddStringParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs addparam string "+name+ " "+ var+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;


def GetStringParam(name,varargin):
  #AddMetadata(name, property, port) 
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
    
    scommand="iogs getparam string "+ name+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;


def SetStringParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;

    scommand="iogs setparam string "+ name+" "+var+" "+str(flag)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;

def AddVecParam(name, var, vsize,flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    vecstring=vectostring(var, vecsize,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #uvecstring=sprintf('""%s""',vecstring); 
  #scommand=sprintf("iogs addparam vec %s %s %d %d %s", name, uvecstring,vsize,flag,  port,server);
    
    scommand="iogs addparam vec "+name+ " "+ vecstring+" "+str(vsize)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;


def GetVecParam(name, vecsize,varargin):
  #AddMetadata(name, property, port)  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    scommand="iogs getparam vec "+ name+" "+str(vecsize)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    vec=stringtovec(result, vecsize,',');
    return vec;
  


def SetVecParam(name, vec, vecsize,flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
    
    vecstring=vectostring(vec, vecsize,',');  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #uvecstring=sprintf('""%s""',vecstring);
  #scommand=sprintf("iogs setparam vec %s %s %d %s", name, uvecstring,vecsize,flag,  port,server);
  #result=os.system(scommand);
  #status=0;
    scommand="iogs setparam vec "+ name+" "+vecstring+" "+str(vecsize)+" "+str(flag)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    result=(res[0].strip())
    return result;




def AddMatParam(name, var, nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;

    i=0
    j=0
    vvar=[]
    while i<nr:
      j=0
      while j<nc:
         vvar.append(var[i][j]);
         j=j+1
      i=i+1
      
    matstring=vectostring(vvar, nr,nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #umatstring=sprintf('""%s""',matstring); 
  #scommand=sprintf("iogs addparam mat %s %s %d %d %d %s", name, umatstring,nr,nc,flag,  port,server);
  #result=os.system(scommand);
  #status=0;

    scommand="iogs addparam mat "+name+ " "+ matstring+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;



def GetMatParam(name, float, nr,nc,varargin):
  #AddMetadata(name, property, port)
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
  
  #scommand=sprintf("iogs getparam mat %s %s %d %d %s", name, float,nr,nc,  port,server);
  #result=os.system(scommand);
  #tmat=stringtovec(result, nr*nc,',');
    scommand="iogs getparam mat "+ name+" "+str(nr)+" "+str(nc)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    vecsize=nr*nc
    tmat=stringtovec(result, vecsize,',');
      
    ind=0;
    i=0
    j=0
    mat=[]
    while i<nr:
      j=0
      while j<nc:
        mat.append(tmat[ind]);
        ind=ind+1;
        j=j+1
      i=i+1
  
    return mat


def SetMatParam(name, var, nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;

    i=0
    j=0
    vvar=[]
    while i<nr:
      j=0
      while j<nc:
         vvar.append(var[i][j]);
         j=j+1
      i=i+1
      
    matstring=vectostring(vvar, nr,nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #umatstring=sprintf('""%s""',matstring); 
  #scommand=sprintf("iogs addparam mat %s %s %d %d %d %s", name, umatstring,nr,nc,flag,  port,server);
  #result=os.system(scommand);
  #status=0;

    scommand="iogs setparam mat "+name+ " "+ matstring+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;









def Addmmat3dParam(name, var, ni,nj,nk,nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    ind=0;
    vvar=[]
    while i1<ni:
      i2=0
      while i2<nj:
        i3=0
        while i3<nk:
          i=0
          while i<nr:
            j=0
            while j<nc:
              vvar.append(var[i1][i2][i3][i][j])
              ind=ind+1;
              j=j+1
            i=i+1
          i3=i3+1
        i2=i2+1
      i1=i1+1
    mm3dstring=vectostring(vvar, ni*nj*nk*nr*nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #umatstring=sprintf('""%s""',matstring); 
  #scommand=sprintf("iogs addparam mat %s %s  %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  port,server);
  #result=os.system(scommand);
  #status=0;

    scommand="iogs addparam mmat3d "+name+ " "+ mm3dstring+" "+str(ni)+" "+str(nj)+" "+str(nk)+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;


def Getmmat3dParam(name, mm3d, ni,nj,nk,nr,nc,varargin):
  #AddMetadata(name, property, port)
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
  
  #scommand=sprintf("iogs getparam mat %s %s %d %d %d %d %d %d %s", name, mm3d,n,nj,nk,nr,nc,  port,server);
  #result=os.system(scommand);
  #tmat=stringtovec(result, ni*nj*nk*nr*nc,',');
    scommand="iogs getparam mmat3d "+ name+" "+" "+str(ni)+" "+str(nj)+" "+str(nk)+" "+str(nr)+" "+str(nc)+" "+str(port)+" "+server
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    mm3dsize=nr*nc*ni*nj*nk
    tmat=stringtovec(result, mm3dsize,',');
    
    ind=0;
    vvar=newmmat3d(ni,nj,nk,nr,nc)
    while i1<ni:
      i2=0
      while i2<nj:
        i3=0
        while i3<nk:
          i=0
          while i<nr:
            j=0
            while j<nc:
              vvar[i1][i2][i3][i][j]=tmat[ind]
              ind=ind+1;
              j=j+1
            i=i+1
          i3=i3+1
        i2=i2+1
      i1=i1+1
    return vvar


def Setmmat3dParam(name, var, ni,nj,nk,nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0:
        server=varargin[0];
        if nargin>1:
          port=varargin[1];
        else:
          port=8080;
    else:
        server='localhost';
        port=8080;
  
    ind=0;
    vvar=[]
    while i1<ni:
      i2=0
      while i2<nj:
        i3=0
        while i3<nk:
          i=0
          while i<nr:
            j=0
            while j<nc:
              vvar.append(var[i1][i2][i3][i][j])
              ind=ind+1;
              j=j+1
            i=i+1
          i3=i3+1
        i2=i2+1
      i1=i1+1
    mm3dstring=vectostring(vvar, ni*nj*nk*nr*nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  #umatstring=sprintf('""%s""',matstring); 
  #scommand=sprintf("iogs addparam mat %s %s  %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  port,server);
  #result=os.system(scommand);
  #status=0;

    scommand="iogs setparam mmat3d "+name+ " "+ mm3dstring+" "+str(ni)+" "+str(nj)+" "+str(nk)+" "+str(nr)+" "+str(nc)+" "+str(flag)+" "+str(port)+" "+server;
    res=os.popen(scommand).readlines()
    result=res[0].strip()
    return result;




    

