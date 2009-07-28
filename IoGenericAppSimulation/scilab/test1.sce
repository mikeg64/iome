exec('../IoSetUpGenericScilabSimulation.sce');  //this should be executed by the iome start up application
//exec('ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramstest1.sce');
//stacksize('max');
//stacksize(268435454);


//simfile=metadata.name+'.xml';
//simfile='mine'
//NewSimulation(metadata.name,'null',elist);
createsim(consts,domain,source,metadata,simfile,elist);

//[consts,domain,source]=loadsim('test1_16_02_09.xml',elist);
//chdir(metadata.directory);

//runsim(consts,domain,source,metadata,simfile,elist);
//WriteSimulation(simfile,elist);
//chdir('..');
//exit();
