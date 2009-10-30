function [matstring]=mattostring(mat,separator) 
  [r,c]=size(mat);
  vtot='';
  for i=1:r
    vin=mat(i,:);
    vs=vectostring(vin,separator);
    vtot=vtot+separator+vs;
  end
  matstring=vtot;
endfunction

