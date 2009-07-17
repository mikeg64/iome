//To use these functions make sure the location of the IOME iogs application
//is on the path
//Linux export IOME_HOME=PATHTOIOME
//Linux export PATH=$PATH":$IOME_HOME/bin"
//Windows set IOME_HOME=PATHTOIOME
//Windows set PATH=%PATH%;$IOME_HOME/bin

function [vec]=stringtovec(stringvar, vsize, separator)
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
endfunction

function [vecstring]=vectostring(vec,separator)
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
  
endfunction

function [result]=GetNSteps(elist)
  //AddMetadata(name, property, port) 
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
  
  try
    scommand=sprintf("iogs getnsteps %d %d %s",  id,port,server);
    sresult=unix_g(scommand);
    result=msscanf(sresult,'%d');
  catch
    disp('GetNSteps Error!');
    result=-1;
  end

  //status=0;
endfunction

function [result]=GetStep(elist)
  //AddMetadata(name, property, port) 
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
  
  try  
    scommand=sprintf("iogs getstep %d %d %s",  id,port,server);
    sresult=unix_g(scommand);
    result=msscanf(sresult,'%d');
  catch
    disp('GetStep Error!');
    result=-1;
  end
  //status=0;
endfunction


function [status]=SetNSteps(var,elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs setnsteps %d %d  %d %s", var,id,  port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('SetNSteps Error!');
    status=-1;
end

endfunction

function [status]=SetStep(var,elist)
  //AddMetadata(name, property, port) 
  
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
  
  try
    scommand=sprintf("iogs setstep %d %d  %d %s", var, id, port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('SetStep Error!');
    status=-1;
  end
endfunction



function [status]=ExitIOME(elist)
  //Stop the server and exit IOME
  
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
  
  
  try
    scommand=sprintf("iogs exitiome %d %d %s",id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('ExitIOME Error!');
    status=-1;
  end
endfunction

function [status]=RunSimulation(simfile, outfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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

  //Start the generic simulation
  //Simulation name
  //Config name
  //State file name
  //port
  try
    scommand=sprintf("iogs runsimulation %s %s %d %d %s",simfile, outfile, id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('RunSimulation Error!');
    status=-1;
  end
endfunction

function [simid]=SubmitSimulation(simfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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

  //Submit the generic simulation
  //Simulation Config name
  //returns
  try
    scommand=sprintf("iogs submitsimulation %s %d %s", simfile, port,server);
    result=unix_g(scommand);
    simid=msscanf(result,'%d');
  catch
    disp('SubmitSimulation Error!');
    simid=-1;
  end
endfunction

function [status]=SimulationStatus(elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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

  //Submit the generic simulation
  //Simulation Config name
  //returns
  try
    scommand=sprintf("iogs simulationstatus %d %d %s", id, port,server);
    result=unix_g(scommand);
    status=msscanf(result,'%d');
  catch
    disp('SimulationStatus Error!');
    status=-1;
  end  
endfunction

function [status]=GetSimulationResult(outfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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

  //Submit the generic simulation
  //Simulation Config name
  //returns
  try  
    scommand=sprintf("iogs getsimulationresult %s %d %d %s", outfile, id,port,server);
    result=unix_g(scommand);
    status=msscanf(result,'%d');
  catch
    disp('GetSimulationResult Error!');
    status=-1;
  end   
endfunction

function [status]=DeleteSimulation(elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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


  //Submit the generic simulation
  //Simulation Config name
  //returns
  try
    scommand=sprintf("iogs deletesimulation %d %d %s", id, port,server);
    result=unix_g(scommand);
    status=msscanf(result,'%d');
  catch
    disp('DeleteSimulation Error!');
    status=-1;
  end   
endfunction


function [status]=ReadSimulation(simfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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


  //Start the generic simulation
  //Simulation name
  //Config name
  //State file name
  //port
  try
    scommand=sprintf("iogs readsimulation %d %s %d %s", simfile, id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('ReadSimulation Error!');
    status=-1;
  end 
endfunction




function [status]=ReadLocalSimulation(simfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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


  //Start the generic simulation
  //Simulation name
  //Config name
  //State file name
  //port
  try
    scommand=sprintf("iogs readlocalsimulation %d %s %d %s", simfile, id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('ReadLocalSimulation Error!');
    status=-1;
  end 
endfunction





function [status]=NewSimulation(simname,xslname, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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


  //Start the generic simulation
  //Simulation name
  //Config name
  //State file name
  //port
  try
    scommand=sprintf("iogs newsimulation %s %s %d %d %s", simname,xslname, id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('NewSimulation Error!');
    status=-1;
  end 
endfunction


function [status]=WriteSimulation(simfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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


  //Start the generic simulation
  //Simulation name
  //Config name
  //State file name
  //port
  try
    scommand=sprintf("iogs writesimulation %s %d %d %s", simfile, id,port,server);
    disp(scommand)
    result=unix_g(scommand);
    simwid=mopen(simfile,'w');
    mfprintf(simwid,'%s',result);
    mclose(simwid);
    
    status=0;
  catch
    disp('WriteSimulation Error!');
    status=-1;
  end 
endfunction




function [status]=WriteLocalSimulation(simfile, elist)
//function [status]=InitIOME(simname, configname, statename,port,server)
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


  //Start the generic simulation
  //Simulation name
  //Config name
  //State file name
  //port
  try
    scommand=sprintf("iogs writelocalsimulation %s %d %d %s", simfile, id,port,server);
    disp(scommand)
    result=unix_g(scommand);
    simwid=mopen(simfile,'w');
    mfprintf(simwid,'%s',result);
    mclose(simwid);
    
    status=0;
  catch
    disp('WriteLocalSimulation Error!');
    status=-1;
  end 
endfunction






function [status]=AddMetadata(name, property,elist)
  //AddMetadata(name, property, port) 
  
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

  
  
  try
    scommand=sprintf("iogs addmetadata %s %s %d %d %s", name, property, id, port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('AddMetadata Error!');
    status=-1;
  end 
endfunction

function [status]=SetMetadata(name, property,elist)
  //SetMetadata(name, property, port)
  
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

  
  try
    scommand=sprintf("iogs setmetadata %s %s %d %d %s", name, property,  id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('SetMetadata Error!');
    status=-1;
  end 
endfunction

function [property]=GetMetadata(name,elist)
  //GetMetadata(name, property, port) 
  
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

  
  try
    scommand=sprintf("iogs getmetadata %s %d %d %s", name, id,port,server);
    property=unix_g(scommand);
    status=0;
  catch
    disp('GetMetadata Error!');
    status=-1;
  end 
endfunction

function [status]=AddDoubleParam(name, doub, flag,elist)
  //AddMetadata(name, property, port) 
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

  
  
  try
    scommand=sprintf("iogs addparam double %s %f %d %d %d %s", name, doub,flag,  id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('AddDoubleParam Error!');
    status=-1;
  end 
endfunction

function [result]=GetDoubleParam(name,elist)
  //AddMetadata(name, property, port) 
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

  
  try
    scommand=sprintf("iogs getparam double %s %d %d %s", name,  id,port,server);
    sresult=unix_g(scommand);
    
    result=msscanf(sresult,'%f');
  catch
    disp('GetDoubleParam Error!');
    result=-1;
  end 
  
  //status=0;
endfunction

function [status]=SetDoubleParam(name, doub,elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs setparam double %s %f %d %d %s", name, doub,  id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('SetDoubleParam Error!');
    status=-1;
  end 
endfunction


function [status]=AddIntParam(name, var, flag,elist)
  //AddMetadata(name, property, port) 
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

  
  
  try  
    scommand=sprintf("iogs addparam int %s %d %d %d %d %s", name, var,flag,  id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('AddIntParam Error!');
    status=-1;
  end 
endfunction

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
  
  try  
   scommand=sprintf("iogs getobjnum %d %d %s", name, var,flag,  id,port,server);
   sresult=unix_g(scommand);
   result=msscanf(sresult,'%d');
  catch
   disp('GetObjNum Error!');
   status=-1;
  end
   
endfunction



function [result]=GetIntParam(name,elist)
  //AddMetadata(name, property, port) 
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

  
  try
    scommand=sprintf("iogs getparam int %s %d %d %s", name,  id,port,server);
    sresult=unix_g(scommand);
    result=msscanf(sresult,'%d');
  catch
   disp('GetIntParam!');
   result=-1;
  end

  //status=0;
endfunction



function [result]=SetIntParam(name, var,elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs setparam int %s %d  %d %d %s", name, var,  id,port,server);
    result=unix_g(scommand);
  catch
   disp('SetIntParam!');
   result=-1;
  end
  
endfunction











function [status]=AddStringParam(name, var, flag,elist)
  //AddMetadata(name, property, port) 
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

  
  
  try
    scommand=sprintf("iogs addparam string %s %s %d %d %d %s", name, var,flag,  id,port,server);
    status=unix_g(scommand);
  catch
    disp('AddStringParam!');
    status=-1;
  end
endfunction

function [result]=GetStringParam(name,elist)
  //AddMetadata(name, property, port) 
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

  
  try
    scommand=sprintf("iogs getparam string %s %d %d %s", name,  id,port,server);
    result=unix_g(scommand);
  catch
    disp('GetStringParam!');
    result=-1;
  end
  
  //status=0;
endfunction

function [status]=SetStringParam(name, var,elist)
  //AddMetadata(name, property, port) 
  
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

  
  try
    scommand=sprintf("iogs setparam string %s %s %d %d %s", name, var,  id,port,server);
    status=unix_g(scommand);
  catch
    disp('SetStringParam!');
    status=-1;
  end
endfunction












function [status]=AddVecParam(name, var, vsize,flag,elist)
  //AddMetadata(name, property, port) 
  
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

  try
    vecstring=vectostring(var,' ');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    uvecstring=sprintf('""%s""',vecstring); 
    scommand=sprintf("iogs addparam vec %s %s %d %d %d %d %s", name, uvecstring,vsize,flag,  id,port,server);
    status=unix_g(scommand);
  catch
    disp('AddVecParam!');
    status=-1;
  end

endfunction

function [vec]=GetVecParam(name, vecsize,elist)
  //AddMetadata(name, property, port)
  
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

  
  try
    scommand=sprintf("iogs getparam vec %s %d %d %d %s", name,vecsize,  id,port,server);
    result=unix_g(scommand);
    vec=stringtovec(result, vecsize,' ');
  catch
    disp('GetVecParam!');
    vec=-1;
  end

endfunction

function [result]=SetVecParam(name, vin, vecsize,elist)
  //AddMetadata(name, property, port) 
  
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

  
  try
    vecstring=vectostring(vin, ',');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    uvecstring=sprintf('""%s""',vecstring);
    scommand=sprintf("iogs setparam vec %s %s %d %d %d %s", name, uvecstring,vecsize,  id,port,server);
    result=unix_g(scommand);
  catch
    disp('SetVecParam!');
    result=-1;
  end
  
endfunction



function [result]=AddMatParam(name, var,flag,elist)
  //AddMetadata(name, property, port) 
  
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


  [nr,nc]=size(var);
  try
      ind=1;
    for i=1:nr
      for j=1:nc
       vvar(ind)=var(i,j);
       ind=ind+1;
      end
    end
     matstring=vectostring(vvar',' ');
     //disp(matstring);
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    umatstring=sprintf('""%s""',matstring);
    
    scommand=sprintf("iogs addparam mat %s %s %d %d %d %d %d %s", name, umatstring,nr,nc,flag,  id,port,server);
    //disp(scommand);
    result=unix_g(scommand);
  catch
    disp('AddParMatam!');
    result=-1;
  end
  
endfunction

function [mat]=GetMatParam(name,nr,nc,elist)
  //AddMetadata(name, property, port)
  
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

  
  try
    scommand=sprintf("iogs getparam mat %s %d %d %d %d %s", name,nr,nc,  id,port,server);
    result=unix_g(scommand);
    tmat=stringtovec(result, nr*nc,' ');
    
    ind=1;
    for i=1:nr
      for j=1:nc
       mat(i,j)=tmat(ind);
       ind=ind+1;
      end
    end
  catch
    disp('GetParamMat error!');
    mat=-1;
  end  
  
  

  status=0;
endfunction

function [vvar]=SetMatParam(name, var, elist)
  //AddMetadata(name, property, port) 
  
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
  try
    [nr,nc]=size(var);
       ind=1;
       vvar=zeros(nr*nc);
    for i=1:nr
      for j=1:nc
       vvar(ind)=var(i,j);
       ind=ind+1;
      end
    end 
    vecstring=vectostring(vvar,' ');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    uvecstring=sprintf('""%s""',vecstring);
    scommand=sprintf("iogs setparam mat %s %s %d %d %d %d %s", name, uvecstring,nr,nc,  id, port,server);
    result=unix_g(scommand);
  catch
    disp('SetMatParam error!');
    result=-1;
  end
  status=0;
endfunction







function [status]=Addmmat3dParam(name, var, ni,nj,nk,nr,nc,flag,elist)
  //AddMetadata(name, property, port) 

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

  try
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
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    umatstring=sprintf('""%s""',matstring); 
    scommand=sprintf("iogs addparam mmat3d %s %s  %d %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  id, port,server);
    status=unix_g(scommand);
    
  catch
    disp('Addmmat3dParam Error!');
    status=-1;
  end
endfunction

function [mat]=Getmmat3dParam(name, ni,nj,nk,nr,nc,elist)
  //AddMetadata(name, property, port)
  
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

  
  try
    scommand=sprintf("iogs getparam mmat3d %s %d %d %d %d %d %d %d %s", name,ni,nj,nk,nr,nc,  id,port,server);
    result=unix_g(scommand);
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
    

    
  catch
    disp('Getmmat3dParam Error!');
    mat=-1;
  end
endfunction

function [vec]=Setmmat3dParam(name, var, ni,nj,nk,nr,nc,elist)
  //AddMetadata(name, property, port) 
  
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

  try
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
    mstring=vectostring(tmat, ni*nj*nk*nr*nc,',');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    umstring=sprintf('""%s""',mstring);
    scommand=sprintf("iogs setparam mmat3d %s %s %d %d %d %d %d  %d %d %s", name, umstring, ni,nj,nk,nr,nc,  id,port,server);
    vec=unix_g(scommand);
  catch
    disp('Setmmat3dParam Error!');
    vec=-1;
  end
endfunction

function [objnum]=GetObjNum(elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs getobjnum %d  %d %s",id,  port,server);
    objnum=unix_g(scommand);
  catch
    disp('GetObjNum Error!');
    objnum=-1;
  end
endfunction

function [numobj]=GetNumObj(elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs getnumobj %d  %d %s", id,  port,server);
    numobj=unix_g(scommand);
  catch
    disp('GetNumObj Error!');
    numobj=-1;
  end  
endfunction

function [status]=GroupBarrier(elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs groupbarrier %d  %d %s", id,  port,server);
    status=unix_g(scommand);
  catch
    disp('GroupBarrier Error!');
    status=-1;
  end  
endfunction




function [status]=DeleteParam(paramname,elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs deleteparam %s %d  %d %s", paramname,id,  port,server);
    status=unix_g(scommand);
  catch
    disp('DeleteParam Error!');
    status=-1;
  end   
endfunction

function [paramlist]=ListParam(paramtype,elist)
  //AddMetadata(name, property, port) 
  
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

  try
    scommand=sprintf("iogs listparam %s %d  %d %s", paramtype,id,  port,server);
    paramlist=unix_g(scommand);
  catch
    disp('ListParam Error!');
    paramlist=-1;
  end   
endfunction






