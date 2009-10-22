//exec('../IoGenericScilabSimulation.sce');  //this should be executed by the iome start up application
//exec('../IoSetUpGenericScilabSimulation.sce');

//tdp=getenv('SCILAB_HOME')+'/share/scilab/contrib/iome_toolbox/loader.sce';
tdp='/usr/share/scilab/contrib/iome_toolbox/loader.sce';
exec(tdp);
exec('ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramstest1.sce');
//stacksize('max');
//stacksize(268435454);



portfile=metadata.name+'0_port.txt';
fd=mopen(portfile,'r');
portid=mfscanf(fd,'%d')
mclose(fd);
elist(2)=portid;


simfile='mysim1.xml';
//NewSimulation(metadata.name,'test1.xsl',elist);
//createsim(consts,domain,source,metadata,simfile,elist);

[consts,domain,source]=loadsim(simfile,elist);
//chdir(metadata.directory);

runsim(consts,domain,source,metadata,simfile,elist);
writesimulation(simfile,elist);
//chdir('..');
//exit();
