function [vec]=stringtovec(stringvar, vsize, separator)
  vec=zeros(vsize,1);
  newformatstring='';
  formatmark='%f'
  for i=1:vsize
    if i>1 then
      formatstring=sprintf("%s%s%s",newformatstring,separator,formatmark);
    else
      formatstring=sprintf("%s",formatmark);
    end
    newformatstring=formatstring;
  end
  vec=msscanf(-1,stringvar,formatstring);
endfunction

