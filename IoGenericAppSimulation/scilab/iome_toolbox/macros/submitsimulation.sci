function [simid]=submitsimulation(simfile, elist)
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

