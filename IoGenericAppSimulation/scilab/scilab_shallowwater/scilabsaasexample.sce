//exec('../../IoSetUpGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('../../IoGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('../ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('../paramssaastest1.sce');
portid=8081;
jobid=2;
//open the file generated
portfile='mysim_port.txt';                            //add comment if  we are not running standalone
//portfile='intsaas1_port.txt';                      //remove comment if  we are not running standalone
//portfile=metadata.name+'_port.txt';
fd=mopen(portfile,'r');
res=mfscanf(fd,'%d %d')
mclose(fd);

elist(2)=res(1);
elist(3)=res(2);

//Add data to logfile

//createsim(consts,domain,source,metadata,simfile,elist);
//WriteSimulation(simfile,elist);
[consts,domain,source]=loadsim('simfile.xml',elist);  //remove comment if we are not running standalone

mkdir(metadata.directory);
mkdir('dx');
runsim(consts,domain,source,elist);

//ExitIOME(elist);                                       //remove comment if we are not running standalone

exit();

t
