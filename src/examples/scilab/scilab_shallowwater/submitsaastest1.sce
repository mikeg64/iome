//this is the standalone version  for submitting work to a saas

exec('../../IoSetUpGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramssaastest1.sce');
//stacksize('max');
//stacksize(268435454);

elistremote=list(2);
elistremote(1)='localhost';
elistremote(2)=8080;

simfile=metadata.name+'.xml';
simfileout=metadata.name+'_out.xml';
NewSimulation(metadata.name,'test1.xsl',elist);
createsim(consts,domain,source,metadata,simfile,elist);

//[consts,domain,source]=loadsim('test1_16_02_09.xml',elist);
//chdir(metadata.directory);
WriteSimulation(simfile,elist);
//runsim(consts,domain,source,metadata,simfile,elist);

RunSimulation(simfile,simfileout,elistremote);

//WriteSimulation(simfile,elist);
//chdir('..');
//exit();
