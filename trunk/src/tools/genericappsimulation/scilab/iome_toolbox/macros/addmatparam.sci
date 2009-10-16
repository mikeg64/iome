function [mat]=addmatparam(name,var,elist)
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
    
    
    vecstring=vectostring(var,' ');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    uvecstring=sprintf('""%s""',vecstring);
    
    
    scommand=sprintf("iogs addparam mat %s %s %d %d 7 %d %d %s", name,uvecstring, nr,nc,  id,port,server);
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
    disp('addmatparam error!');
    mat=-1;
  end  
  
  

  status=0;
endfunction

