function [cam,settings,metadata]=loadcollabsim(simfile,elist)
//loads a simulation file and sets the consts and domains
//elist=list();  parameter used by iome to contain port and server address
ReadSimulation(simfile,elist)

// Camera parameters
cam.camfrom=getvecparam('camfrom',3,elist)  ;//= [25 25 21];
cam.camto=getvecparam('camto',3,elist)  ;//= [23 25 0];
cam.camup=getvecparam('camup',3,elist)  ;//= [23 25 0];
cam.camwidth =getfloatparam('camwidth',elist);//= 47;

settings.step=getintparam('step',elist); //= 1;
settings.name=getstringparam('name',elist);

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

addvecparam('camfrom',cam.camfrom,3,7,elist)  ;//= [25 25 21];
addvecparam('camto',cam.camto,3,7,elist)  ;//= [23 25 0];
addvecparam('camup',cam.camup,3,7,elist)  ;//= [23 25 0];
addfloatparam('camwidth',cam.camwidth,7,elist);//= 47;

addintparam('step',settings.step,7,elist); //= 1;
addstringparam('name',settings.name,7,elist);




endfunction

