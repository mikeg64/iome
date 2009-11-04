//tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
tdp='/usr/share/scilab/contrib/iome_toolbox/loader.sce';
exec(tdp)
exec('iocollabshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramscollabtest1.sce');
//stacksize('max');
//stacksize(268435454);
portfile=metadata.name+'0_port.txt';
fd=mopen(portfile,'r');
portid=mfscanf(fd,'%d')
mclose(fd);
elist(2)=portid;
//elist(2)=portid;

simfile=metadata.name+'.xml';
//NewSimulation(metadata.name,'null',elist);
createcollabsim(cam,settings,metadata,simfile,elist);

//[cam,settings,metadata]=loadcollabsim('test1_16_02_09.xml',elist);



//WriteSimulation(simfile,elist);
//chdir('..');
//exit();
