function [status]=setmetadata(name, property,elist)
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

  uprop=sprintf('""%s""',property); 
  try
    scommand=sprintf("iogs setmetadata %s %s %d %d %s", name, uprop,  id,port,server);
    result=unix_g(scommand);
    status=0;
  catch
    disp('SetMetadata Error!');
    status=-1;
  end 
endfunction

