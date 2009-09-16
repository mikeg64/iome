function [status]=deletesimulation(elist)
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

