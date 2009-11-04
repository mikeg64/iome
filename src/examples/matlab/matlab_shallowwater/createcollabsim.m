function []=createcollabsim(cam,settings,metadata,simfile,elist)

%elist=list();  parameter used by iome to contain port and server address
%elist=list();

addmetadata('author',metadata.author,elist);
addmetadata('date',metadata.sdate,elist);
addmetadata('platform',metadata.platform,elist);
addmetadata('description',metadata.desc,elist);
addmetadata('name',metadata.name,elist);

addparamvec('camfrom',cam.camfrom,3,elist)  ;%= [25 25 21];
addparamvec('camto',cam.camto,3,elist)  ;%= [23 25 0];
addparamvec('camup',cam.camup,3,elist)  ;%= [23 25 0];
addparamdouble('camwidth',cam.camwidth,elist);%= 47;

addparamint('step',settings.step,elist); %= 1;
addparamstring('name',settings.name,elist);






