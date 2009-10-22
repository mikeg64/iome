//used under linux
//tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
tdp='/usr/share/scilab/contrib/iome_toolbox/loader.sce';
//following used under windows
//tdp=getenv('SCILAB_HOME')+'/contrib/iome_toolbox/loader.sce';
exec(tdp);

elist=iome('localhost',8080,0);
addparamdouble('f1',27,elist);
f1=getparamdouble('f1',elist);
addparamint('i1',54,elist);
i1=getparamdouble('i1',elist);
v1=rand(3,1);
addparamvec('v1',v1,elist);
//vectors always returned as row vector
v2=getparamvec('v1',3,elist);

m1=rand(5,3);
addparammat('m1',m1,elist);
m2=getparammat('m1',5,3,elist);





