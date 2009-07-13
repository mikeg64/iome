exec('../../IoSetUpGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('ioshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramssaastest1.sce');

//open the file generated
portfile='mysim_port.txt';                            //add comment if  we are not running standalone
//portfile='intsaas1_port.txt';                      //remove comment if  we are not running standalone
//portfile=metadata.name+'_port.txt';
fd=mopen(portfile,'r');
portid=mfscanf(fd,'%d')
mclose(fd);

elist(2)=portid;

//Add data to logfile

//createsim(consts,domain,source,metadata,simfile,elist);
//WriteSimulation(simfile,elist);
//[consts,domain,source]=loadsim('simfile.xml',elist);  //remove comment if we are not running standalone
runsim(consts,domain,source,elist);

//ExitIOME(elist);                                       //remove comment if we are not running standalone

exit();


