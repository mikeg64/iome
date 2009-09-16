function [cam,settings,metadata]=loadcollabsim(simfile,elist)
//loads a simulation file and sets the consts and domains
//elist=list();  parameter used by iome to contain port and server address
ReadSimulation(simfile,elist)

// Camera parameters
cam.camfrom=GetVecParam('camfrom',3,elist)  ;//= [25 25 21];
cam.camto=GetVecParam('camto',3,elist)  ;//= [23 25 0];
cam.camup=GetVecParam('camup',3,elist)  ;//= [23 25 0];
cam.camwidth =GetFloatParam('camwidth',elist);//= 47;

settings.step=GetIntParam('step',elist); //= 1;
settings.name=GetStringParam('name',elist);

metadata.author=GetMetadata('author',elist);
metadata.sdate=GetMetadata('date',elist);
metadata.platform=GetMetadata('platform',elist);
metadata.desc=GetMetadata('description',elist);
metadata.name=GetMetadata('name',elist);

endfunction

function []=createcollabsim(cam,settings,metadata,simfile,elist)

//elist=list();  parameter used by iome to contain port and server address
//elist=list();

AddMetadata('author',metadata.author,elist);
AddMetadata('date',metadata.sdate,elist);
AddMetadata('platform',metadata.platform,elist);
AddMetadata('description',metadata.desc,elist);
AddMetadata('name',metadata.name,elist);

AddVecParam('camfrom',cam.camfrom,3,7,elist)  ;//= [25 25 21];
AddVecParam('camto',cam.camto,3,7,elist)  ;//= [23 25 0];
AddVecParam('camup',cam.camup,3,7,elist)  ;//= [23 25 0];
AddFloatParam('camwidth',cam.camwidth,7,elist);//= 47;

AddIntParam('step',settings.step,7,elist); //= 1;
AddStringParam('name',settings.name,7,elist);




endfunction

