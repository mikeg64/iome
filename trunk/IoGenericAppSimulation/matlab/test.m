%test.sce

vstr='1.2 1.3 1.4 1.5';
vres=zeros(4,1);
vsize=4;
  newformatstring='';
  formatmark='%f'
  for i=1:vsize
    formatstring=sprintf("%s %s",newformatstring,formatmark);
    newformatstring=formatstring;
  end
  
%[n,vres(1),vres(2)]=msscanf(2,"%f",vstr);
vres=msscanf(-1,vstr,formatstring);

selist.server='localhost';
selist.port=8080;
selist.id=0;

elist=struct2cell(selist);

nargin=length(elist)
server=elist{1}
port=elist{2}

  if nargin>0 then
    server=elist{1};
    if nargin>1 then
      port=elist{2};
      if nargin>2 then
         id=elist{3};
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



