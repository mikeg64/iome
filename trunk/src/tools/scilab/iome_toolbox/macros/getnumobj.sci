function [numobj]=getnumobj(elist)
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

