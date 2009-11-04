function [status]=addparamvec(name, var, elist)
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
    flag=7;
    [l1,l2]=size(var);
    if l1>l2
      len=l1;
      nvar=var';
    else
      len=l2;
      nvar=var;
    end  
    
    vecstring=vectostring(nvar,',');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    //uvecstring=sprintf('""%s""',vecstring); 
    scommand=sprintf("iogs addparam vec %s %s %d %d %d %d %s", name, vecstring,len,flag,  id,port,server);
    unix_g(scommand);
    status=0;
  catch
    disp('AddVecParam!');
    status=-1;
  end

endfunction

