function [status]=addmmat3dparam(name, var, ni,nj,nk,nr,nc,flag,elist)
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
      ind=1;
      for i1=1:ni
         for i2=1:nj
            for i3=1:nk
              for i=1:nr
                for j=1:nc
                 vvar(ind)=var(i1,i2,i3,i,j);
                 ind=ind+1;
                end
              end
          end
        end
      end
     matstring=vectostring(vvar, ni*nj*nk*nr*nc,',');
    
    //put double quotes around the vec string so that it is
    //passed into unix shell script as a single variable
    umatstring=sprintf('""%s""',matstring); 
    scommand=sprintf("iogs addparam mmat3d %s %s  %d %d %d %d %d %d %d %d %s", name, umatstring,ni,nj,nk,nr,nc,flag,  id, port,server);
    status=unix_g(scommand);
    
  catch
    disp('Addmmat3dParam Error!');
    status=-1;
  end
endfunction

