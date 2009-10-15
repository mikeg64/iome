//this should be executed by the iome start up application
exec('ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramssteeringtest1.sce');
//stacksize('max');
//stacksize(268435454);
//open the file generated
portfile=metadata.name+'_port.txt';
fd=mopen(portfile,'r');
portid=mfscanf(fd,'%d')
mclose(fd);

elist(2)=portid;

simfile=metadata.name+'.xml';
//NewSimulation(metadata.name,'test1.xsl',elist);
createsim(consts,domain,source,metadata,simfile,elist);

//[consts,domain,source]=loadsim('test1_16_02_09.xml',elist);
//chdir(metadata.directory);

runsim(consts,domain,source,metadata,simfile,elist);
WriteSimulation(simfile,elist);
//chdir('..');
//exit();
