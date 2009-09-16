function [vecstring]=vectostring(vec,separator)
  [r,vsize]=size(vec);
  vecstring='';
  for i=1:vsize
    if i>1 then
      newvecstring=sprintf("%s%s%f",vecstring,separator,vec(i));
    else
      newvecstring=sprintf("%f",vec(i));    
    end
    vecstring=newvecstring;
  end
  
endfunction

