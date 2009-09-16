%To use these functions make sure the location of the IOME iogs application
%is on the path
%Linux export IOME_HOME=PATHTOIOME
%Linux export PATH=$PATH":$IOME_HOME/bin"
%Windows set IOME_HOME=PATHTOIOME
%Windows set PATH=%PATH%;$IOME_HOME/bin

function [vec]=stringtovec(stringvar, vsize, separator)
  vec=zeros(vsize,1);
  newformatstring='';
  formatmark='%f'
  for i=1:vsize
    if i>1 then
      formatstring=sprintf('%s%s%s',newformatstring,separator,formatmark);
    else
      formatstring=sprintf('%s',formatmark);
    end
    newformatstring=formatstring;
  end
  vec=msscanf(-1,stringvar,formatstring);
%endfunction

function [vecstring]=vectostring(vec,separator)
  [r,vsize]=size(vec);
  vecstring='';
  for i=1:vsize
    if i>1 then
      newvecstring=sprintf('%s%s%f',vecstring,separator,vec(i));
    else
      newvecstring=sprintf('%f',vec(i));    
    end
    vecstring=newvecstring;
  end
  
%endfunction

function [result]=GetNSteps(elist)
  %function [result]=GetNSteps(elist) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  
  %scommand=sprintf('iogs getnsteps %d %d %s',  id,port,server);
  %sresult=unix_g(scommand);
  %result=msscanf(sresult,'%d');
  result=getnsteps(obj,id);
  %status=0;
%endfunction

function [result]=GetStep(elist)
  %function [result]=GetStep(elist)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  %scommand=sprintf('iogs getstep %d %d %s',  id,port,server);
  %sresult=unix_g(scommand);
  %result=msscanf(sresult,'%d');
    result=getstep(obj,id);
  %status=0;
%endfunction


function [status]=SetNSteps(var,elist)
  %function [status]=SetNSteps(var,elist)
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  status=setnsteps(obj,id,var);
%endfunction

function [status]=SetStep(var,elist)
  %function [status]=SetStep(var,elist) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  status=setstep(obj,id,var);
%endfunction



function [status]=ExitIOME(elist)
  %function [status]=ExitIOME(elist)
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport]; 
  
  status=exitiome(obj,id);
  
  
%endfunction

function [results]=RunSimulation(simfile, outfile, elist)
%function [status]=RunSimulation(simfile, outfile, elist)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  %Start the generic simulation
  %Simulation name
  %Config name
  %State file name
  %port
  
  
  results= runsimulation(obj,id,simfilecontent);
%endfunction

function [simid]=SubmitSimulation(simfile, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  %Submit the generic simulation
  %Simulation Config name
  %returns
  
  
  simid=submitsimulation(obj,simfile);
  
%endfunction

function [status]=SimulationStatus(elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  %Submit the generic simulation
  %Simulation Config name
  %returns
  
  
  status=simulationstatus(obj,id);
  
%endfunction

function [result]=GetSimulationResult(outfile, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  %Submit the generic simulation
  %Simulation Config name
  %returns
  
  
  result=getsimulationresults(obj,isimid);
  
%endfunction

function [status]=DeleteSimulation(elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  %Submit the generic simulation
  %Simulation Config name
  %returns
  
  
  status=deletesimulation(obj,id);
  
%endfunction


function [status]=ReadSimulation(simfile, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  %Start the generic simulation
  %Simulation name
  %Config name
  %State file name
  %port
  
  
  status=readsimulation(obj,id,simfile);
%endfunction

function [status]=NewSimulation(simname,xslname, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  %Start the generic simulation
  %Simulation name
  %Config name
  %State file name
  %port
  
  
  status=newsimulation(obj,id,simname,xslname);
%endfunction


function [status]=WriteSimulation(simfile, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  %Start the generic simulation
  %Simulation name
  %Config name
  %State file name
  %port
  
  
  status=writesimulation(obj,id,simfile);
%endfunction


function [status]=AddMetadata(name, property,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport]; 
  
  
  
  status=addmetadata(obj,id,name,property);
%endfunction

function [status]=SetMetadata(name, property,elist)
  %SetMetadata(name, property, port)
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

    sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  status=setmetadata(obj,id,name,property);
  
  
%endfunction

function [property]=GetMetadata(name,elist)
  %GetMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

    sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  property=getmetadata(obj,id,name);
  
 %endfunction

function [status]=AddDoubleParam(name, id,doub, flag,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  status=addparamdouble(obj, id,name,doub,flag);
  
 %endfunction

function [result]=GetDoubleParam(name,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  
  
  result=getparamdouble(obj, id,name);
  
  
%endfunction

function [status]=SetDoubleParam(name, doub,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  
  status=setparamdouble(obj, id,name,doub);

%endfunction


function [status]=AddIntParam(name, var, flag,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  
  
  
    status=addparamint(obj, id,name,var,flag);

%endfunction





function [result]=GetIntParam(name,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

    result=getparamint(obj, id,name);

%endfunction



function [status]=SetIntParam(name, var,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  
      status=setparamint(obj, id,name,var);

%endfunction











function [status]=AddStringParam(name, var, flag,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

     status=addparamstring(obj, id,name,var,flag);

%endfunction

function [result]=GetStringParam(name,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

      result=getparamstring(obj, id,name);

%endfunction

function [status]=SetStringParam(name, var,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  
   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

       status=setparamstring(obj, id,name,var);

%endfunction












function [status]=AddVecParam(name, var, vsize,flag,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  status=addparamvec(obj, id,name,var,vsize,flag);

%endfunction

function [vec]=GetVecParam(name, vecsize,elist)
  %AddMetadata(name, property, port)
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

   vec=getparamvec(obj, id,name,vecsize);

%endfunction

function [vin]=SetVecParam(name, vin, vecsize,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

   status=setparamvec(obj, id,name,vin,vecsize);

%endfunction



function [status]=AddMatParam(name, var,flag,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  [nr,nc]=size(var);
  rvar=reshape(var,1,nr*nc);
  status=addparammat(obj, id,name,rvar,nr,nc,flag);

 %   ind=1;
 % for i=1:nr
 %   for j=1:nc
 %    vvar(ind)=var(i,j);
 %    ind=ind+1;
%    end
%  end
    status=addparammat(obj, id,name,rvar,nr,nc,flag);

%endfunction

function [mat]=GetMatParam(name,nr,nc,elist)
  %AddMetadata(name, property, port)
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
 
  res=getparammat(obj, id,name,nr,nc);
  mat=reshape(res,nr,nc);
%endfunction

function [vvar]=SetMatParam(name, var, elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  
 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  [nr,nc]=size(var);
  rvar=reshape(var,1,nr*nc);
 

    status=setparammat(obj, id,name,rvar,nr,nc);

  
%endfunction







function [status]=Addmmat3dParam(name, var, ni,nj,nk,nr,nc,flag,elist)
  %AddMetadata(name, property, port) 

  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  
  
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
   
  status=addparammat3d(obj, id,name,vvar,ni,nj,nk,nr,nc,flag);

%endfunction

function [mat]=Getmmat3dParam(name, ni,nj,nk,nr,nc,elist)
  %AddMetadata(name, property, port)
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
 
    tmat=getparammat3d(obj, id,name,ni,nj,nk,nr,nc);

    
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
  

  
%endfunction

function [status]=Setmmat3dParam(name, var, ni,nj,nk,nr,nc,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

    ind=1;
    for i1=1:ni
       for i2=1:nj
          for i3=1:nk
            for i=1:nr
              for j=1:nc
               tmat(ind)=var(i1,i2,i3,i,j);
               ind=ind+1;
              end
            end
        end
      end
    end
    status=setparammat3d(obj, id,name,tmat,ni,nj,nk,nr,nc);

%endfunction


function [result]=GetObjNum(elist)
  
 nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
  
 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  result=getobjnum(obj,id);

   
    
%endfunction



function [numobj]=GetNumObj(elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  
  numobj=getnumobj(obj,id);
  
%endfunction

function [status]=GroupBarrier(myid,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  %try
  %  scommand=sprintf("iogs groupbarrier %d  %d %s", id,  port,server);
  %  status=system(scommand);
  %catch
  %  disp('GroupBarrier Error!');
  %  status=-1;
  %end
 
  testnotcomplete=1;
  numobj=getnumobj(obj,id);
  
  if numobj>1
    iprocstate=zeros(nmobj);
    
    %this proc has already reached the barrier
    setgroupbarrier(obj,myid,1);
    iprocstate(myid+1)=1;
    
    
    while testnotcomplete==1
      for i=1:numobj
        if iprocstate(i)==0
           state=testgroupbarrier(obj,i-1);
           if state == 0
              testnotcomplete=1;
           else
              iprocstate(i)=1;
           end
        
        
        end  %if iprocstate(i)==0
      
      end %for i=1:numobj
    
    end %testnotcomplete==1
    setgroupbarrier(obj,myid,0);
  
  end %if numobj>1
  
  
  
%endfunction




function [status]=DeleteParam(paramname,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  
  
  status=deleteparam(obj,id,paramname);
  
%endfunction

function [paramlist]=ListParam(paramtype,elist)
  %AddMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 then
    server=elist(1);
    if nargin>1 then
      port=elist(2);
      if nargin>2 then
         id=elist(3);
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end
 sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];

  
  
  paramlist=listparam(id,paramtype);
  
%%endfunction






