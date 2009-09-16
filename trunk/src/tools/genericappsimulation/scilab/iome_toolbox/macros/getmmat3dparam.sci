function [mat]=getmmat3dparam(name, ni,nj,nk,nr,nc,elist)
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
    scommand=sprintf("iogs getparam mmat3d %s %d %d %d %d %d %d %d %s", name,ni,nj,nk,nr,nc,  id,port,server);
    result=unix_g(scommand);
    tmat=stringtovec(result, ni*nj*nk*nr*nc,',');
      
      ind=1;
      for i1=1:ni
         for i2=1:nj
            for i3=1:nk
              for i=1:nr
                for j=1:nc
                 mat(i1,i2,i3,i,j)=tmat(ind);
                 ind=ind+1;
                end
              end
          end
        end
      end
    

    
  catch
    disp('Getmmat3dParam Error!');
    mat=-1;
  end
endfunction

