//test.sce

vstr='1.2 1.3 1.4 1.5';
vres=zeros(4,1);
vsize=4;
  newformatstring='';
  formatmark='%f'
  for i=1:vsize
    formatstring=sprintf("%s %s",newformatstring,formatmark);
    newformatstring=formatstring;
  end
//[n,vres(1),vres(2)]=msscanf(2,"%f",vstr);
vres=msscanf(-1,vstr,formatstring);


