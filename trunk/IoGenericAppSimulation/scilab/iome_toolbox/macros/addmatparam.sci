function [mat]=addmatparam(name,nr,nc,elist)
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

