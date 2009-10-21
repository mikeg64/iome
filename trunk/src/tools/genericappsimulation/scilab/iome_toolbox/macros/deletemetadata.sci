function [status]=deletemetadata(name,elist)
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
    scommand=sprintf("iogs deletemetadata %s %d  %d %s", name,id,  port,server);
    status=unix_g(scommand);
  catch
    disp('DeleteMetadata Error!');
    status=-1;
  end   
endfunction

