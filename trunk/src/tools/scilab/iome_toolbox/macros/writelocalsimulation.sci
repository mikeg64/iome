function [status]=writelocalsimulation(simfile, elist)
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

