function [cam,settings,metadata]=loadcollabsim(simfile,elist)
//loads a simulation file and sets the consts and domains
//elist=list();  parameter used by iome to contain port and server address
readsimulation(simfile,elist)

// Camera parameters
cam.camfrom=getparamvec('camfrom',3,elist)  ;//= [25 25 21];
cam.camto=getparamvec('camto',3,elist)  ;//= [23 25 0];
cam.camup=getparamvec('camup',3,elist)  ;//= [23 25 0];
cam.camwidth =getparamdouble('camwidth',elist);//= 47;

settings.step=getparamint('step',elist); //= 1;
settings.name=getparamstring('name',elist);

metadata.author=getmetadata('author',elist);
metadata.sdate=getmetadata('date',elist);
metadata.platform=getmetadata('platform',elist);
metadata.desc=getmetadata('description',elist);
metadata.name=getmetadata('name',elist);

endfunction

function []=createcollabsim(cam,settings,metadata,simfile,elist)

//elist=list();  parameter used by iome to contain port and server address
//elist=list();

addmetadata('author',metadata.author,elist);
addmetadata('date',metadata.sdate,elist);
addmetadata('platform',metadata.platform,elist);
addmetadata('description',metadata.desc,elist);
addmetadata('name',metadata.name,elist);

addparamvec('camfrom',cam.camfrom,3,elist)  ;//= [25 25 21];
addparamvec('camto',cam.camto,3,elist)  ;//= [23 25 0];
addparamvec('camup',cam.camup,3,elist)  ;//= [23 25 0];
addparamdouble('camwidth',cam.camwidth,elist);//= 47;

addparamint('step',settings.step,elist); //= 1;
addparamstring('name',settings.name,elist);




endfunction

