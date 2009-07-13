#!/usr/bin/python


#Run this program 
import os


# import MySQL module
import MySQLdb
#load connection data
f=open('../input/dbin.txt','r')
dbhost=f.readline().strip()
dbuser=f.readline().strip()
dbpass=f.readline().strip()
dbdb=f.readline().strip()
f.close()


#Read from each account db and update payement information
# connect
db = MySQLdb.connect(host=dbhost, user=dbuser, passwd=dbpass, db=dbdb)
# create a cursor
cursor = db.cursor()

#dbtable="acegg"
#dbtable="acabbey"
dbtable="acybseisa"

dbpaytable="payments"
currentacid=0
currentpayid=0

selectpayitems="""SELECT * FROM """+dbpaytable+""" WHERE accountname="""+dbtable
result=cursor.execute(selectpayitems);

for row in result:
    payid=row[0]
    payday=row[1]
    paymonth=row[2]
    payyear=row[3]
    payalias=row[4]
    payacname=row[5]
    paypaymentname=row[6]
    paycredit=row[7]
    paydebit=row[8]
    payoutstandng=row[9]
    paytotal=row[10]
    paydebitinterest=row[11]
    paycreditinterest=row[12]
    paypaymode=row[13]
    #find all the payments made from the account table with id > maxid
    #and name=paymentname
    selectpayments="""SELECT * FROM """+dbtable+"""WHERE id>"""+currentacid+""" AND name="""+paypaymentname
    selpaysres=cursor.execute(selectpayments);
    #now take each of the payments read and write them to the paymentsmade database
    for spayrow in selpayres:
        opayid=currentpayid+1
        opayday=spayrow[1]
        opaymonth=spayrow[2]
        opayyear=spayrow[3]
        opayalias=payalias
        opayacname=payacname
        opayapymentname=paypaymentname
        opaycredit=spayrow[6]
        opaydebit=spayrow[5]
        opayoutstanding=spayrow[7]
        opaytotal=paytotal
        opaycreditinterest=paycreditinterest
        opaypaymode=paypaymode
        #add new entry to payment made table
        insertdata="""INSERT INTO paymentsmade (id, day, month, year, alias, accountname, paymentname, credit, debit, outstanding, total, debitinterest, creditinterest, paymode) VALUES ("""
        svalues=" "+str(currentpayid)+", "+day+", "+month+", "+year+""", " """+name+""" ","""+debit+", "+credit+","+balance+""")"""
        cursor.execute(insertdata+svalues)
        currentpayid=currentpayid+1        
    
#To use these defs make sure the location of the IOME iogs application
#is on the path
#Linux export IOME_HOME=PATHTOIOME
#Linux export PATH=$PATH":$IOME_HOME/bin"
#Windows set IOME_HOME=PATHTOIOME
#Windows set PATH=%PATH%;$IOME_HOME/bin

def stringtovec(stringvar, vsize, separator):
  vec=zeros(vsize,1);
  newformatstring='';
  formatmark='%f'
  for i=1:vsize
    if i>1 then
      formatstring=sprintf("%s%s%s",newformatstring,separator,formatmark);
    else
      formatstring=sprintf("%s",formatmark);
    end
    newformatstring=formatstring;
  end
  vec=msscanf(-1,stringvar,formatstring);


def [vecstring]=vectostring(vec,separator):
  [r,vsize]=size(vec);
  vecstring='';
  for i=1:vsize
    if i>1 then
      newvecstring=sprintf("%s%s%f",vecstring,separator,vec(i));
    else
      newvecstring=sprintf("%f",vec(i));    
    end
    vecstring=newvecstring;
  end
  


def InitIOME(simname, configname, statename, varargin):
#def [status]=InitIOME(simname, configname, statename,port,server)
  nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end

  #Start the generic simulation
  #Simulation name
  #Config name
  #State file name
  #port
  
  scommand=sprintf("iogs startiome %s %s %s %d", simname, configname, statename, port,server);
  result=os.system(scommand);
  status=0;


def ExitIOME():
  #Stop the server and exit IOME
  scommand=sprintf("iogs exitiome");
  result=os.system(scommand);
  status=0;




def AddMetadata(name, property,varargin):
  #AddMetadata(name, property, port) 
  
    nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  
  scommand=sprintf("iogs addmetadata %s %s %d %s", name, property,  port,server);
  result=os.system(scommand);
  status=0;


def SetMetadata(name, property,varargin):
  #SetMetadata(name, property, port)
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs addmetadata %s %s %d", name, property,  port,server);
  result=os.system(scommand);
  status=0;


def GetMetadata(name,varargin):
  #GetMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getmetadata %s %d %s", name, port,server);
  property=os.system(scommand);
  status=0;


def AddFloatParam(name, float, flag,varargin):
  #AddMetadata(name, property, port) 
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  
  scommand=sprintf("iogs addparam float %s %f %d %d %s", name, float,flag,  port,server);
  result=os.system(scommand);
  status=0;


def GetFloatParam(name,varargin):
  #AddMetadata(name, property, port) 
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getparam float %s %d %d %s", name,  port,server);
  sresult=os.system(scommand);
  
  result=msscanf(sresult,'%f');
  
  #status=0;


def SetFloatParam(name, float, flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  scommand=sprintf("iogs setparam float %s %s %d %s", name, float,flag,  port,server);
  result=os.system(scommand);
  status=0;



def AddIntParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  
  scommand=sprintf("iogs addparam int %s %d %d %d %s", name, var,flag,  port,server);
  result=os.system(scommand);
  status=0;


def GetIntParam(name,varargin):
  #AddMetadata(name, property, port) 
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getparam int %s %d %d %s", name,  port,server);
  sresult=os.system(scommand);
  result=msscanf(sresult,'%d');

  #status=0;


def SetIntParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  scommand=sprintf("iogs setparam int %s %d %d %s", name, var,flag,  port,server);
  result=os.system(scommand);
  status=0;












def AddStringParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  
  scommand=sprintf("iogs addparam string %s %s %d %d %s", name, var,flag,  port,server);
  result=os.system(scommand);
  status=0;


def GetStringParam(name,varargin):
  #AddMetadata(name, property, port) 
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getparam string %s %d %d %s", name,  port,server);
  result=os.system(scommand);
  #status=0;


def SetStringParam(name, var, flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  scommand=sprintf("iogs setparam string %s %s %d %s", name, var,flag,  port,server);
  result=os.system(scommand);
  status=0;













def AddVecParam(name, var, vsize,flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
   vecstring=vectostring(var, vecsize,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  uvecstring=sprintf('""%s""',vecstring); 
  scommand=sprintf("iogs addparam vec %s %s %d %d %s", name, uvecstring,vsize,flag,  port,server);
  result=os.system(scommand);
  status=0;


def GetVecParam(name, float, vecsize,varargin):
  #AddMetadata(name, property, port)
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getparam vec %s %s %d %s", name, float,vecsize,  port,server);
  result=os.system(scommand);
  vec=stringtovec(result, vecsize,',');

  status=0;


def SetVecParam(name, float, vecsize,flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  vecstring=vectostring(vec, vecsize,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  uvecstring=sprintf('""%s""',vecstring);
  scommand=sprintf("iogs setparam vec %s %s %d %s", name, uvecstring,vecsize,flag,  port,server);
  result=os.system(scommand);
  status=0;




def AddMatParam(name, var, nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
    ind=1;
  for i=1:nr
    for j=1:nc
     vvar(ind)=var(i,j);
     ind=ind+1;
    end
  end
   matstring=vectostring(vvar, nr,nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  umatstring=sprintf('""%s""',matstring); 
  scommand=sprintf("iogs addparam mat %s %s %d %d %d %s", name, umatstring,nr,nc,flag,  port,server);
  result=os.system(scommand);
  status=0;


def GetMatParam(name, float, nr,nc,varargin):
  #AddMetadata(name, property, port)
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getparam mat %s %s %d %d %s", name, float,nr,nc,  port,server);
  result=os.system(scommand);
  tmat=stringtovec(result, nr*nc,',');
  
  ind=1;
  for i=1:nr
    for j=1:nc
     mat(i,j)=tmat(ind);
     ind=ind+1;
    end
  end
  
  
  

  status=0;


def SetMatParam(name, var, nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
     ind=1;
  for i=1:nr
    for j=1:nc
     vvar(ind)=var(i,j);
     ind=ind+1;
    end
  end 
  vecstring=vectostring(vvar, nr*nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  uvecstring=sprintf('""%s""',vecstring);
  scommand=sprintf("iogs setparam vec %s %s %d %s", name, uvecstring,nr,nc,flag,  port,server);
  result=os.system(scommand);
  status=0;








def Addmmat3dParam(name, var, ni,nj,nk,nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
    ind=1;
    for i1=1:ni
       for i2=1:nj
          for i3=1:nk
            for i=1:nr
              for j=1:nc
               vvar(ind)=var(i1,i2,i3,i,j);
               ind=ind+1;
              end
            end
        end
      end
    end
   matstring=vectostring(vvar, ni*nj*nk*nr*nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  umatstring=sprintf('""%s""',matstring); 
  scommand=sprintf("iogs addparam mat %s %s  %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  port,server);
  result=os.system(scommand);
  status=0;


def Getmmat3dParam(name, mm3d, ni,nj,nk,nr,nc,varargin)
  #AddMetadata(name, property, port)
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
  
  scommand=sprintf("iogs getparam mat %s %s %d %d %d %d %d %d %s", name, mm3d,n,nj,nk,nr,nc,  port,server);
  result=os.system(scommand);
  tmat=stringtovec(result, ni*nj*nk*nr*nc,',');
    
    ind=1;
    for i1=1:ni
       for i2=1:nj
          for i3=1:nk
            for i=1:nr
              for j=1:nc
               mat(i1,i2,i3,i,j)=tmat(ind);
               ind=ind+1;
              end
            end
        end
      end
    end
  

  status=0;


def Setmmat3dParam(name, var, ni,nj,nk,nr,nc,flag,varargin):
  #AddMetadata(name, property, port) 
  
      nargin=len(varargin);
    if nargin>0 then
    server=varargin(0);
    if nargin>1 then
      port=varargin(1);
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
  end
  
    ind=1;
    for i1=1:ni
       for i2=1:nj
          for i3=1:nk
            for i=1:nr
              for j=1:nc
               tmat(ind)=var(i1,i2,i3,i,j)=;
               ind=ind+1;
              end
            end
        end
      end
    end
  mstring=vectostring(tmat, ni*nj*nk*nr*nc,',');
  
  #put double quotes around the vec string so that it is
  #passed into unix shell script as a single variable
  umstring=sprintf('""%s""',mstring);
  scommand=sprintf("iogs setparam mmat3d %s %s %d %d %d %d %d %d %d %s", name, umstring, ni,nj,nk,nr,nc,flag,  port,server);
  result=os.system(scommand);
  status=0;




    

