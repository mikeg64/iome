function [result]=setvecparam(name, vin,elist)
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
    
    [l1,l2]=size(vin);
    if l1>l2
      len=l1;
    else
      len=l2;
    end
    vecstring=vectostring(vin, ',');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    uvecstring=sprintf('""%s""',vecstring);
    scommand=sprintf("iogs setparam vec %s %s %d %d %d %s", name, uvecstring,len,  id,port,server);
    result=unix_g(scommand);
  catch
    disp('SetVecParam!');
    result=-1;
  end
  
endfunction

