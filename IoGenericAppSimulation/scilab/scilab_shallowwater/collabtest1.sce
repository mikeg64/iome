exec('../../IoSetUpGenericScilabSimulation.sce');  //this should be executed by the iome start up application
exec('iocollabshallowwater.sce');

//this application is started using the io  start scilab application
exec('paramscollabtest1.sce');
//stacksize('max');
//stacksize(268435454);
//open the file generated
//portfile='mysim0_port.txt';                            //add comment if  we are not running standalone
//portfile='intsaas1_port.txt';                      //remove comment if  we are not running standalone
//portfile=metadata.name+'_port.txt';
//fd=mopen(portfile,'r');
//portid=mfscanf(fd,'%d')
//mclose(fd);

//elist(2)=portid;

simfile=metadata.name+'.xml';
//NewSimulation(metadata.name,'null',elist);
//createcollabsim(cam,settings,metadata,simfile,elist);

//[cam,settings,metadata]=loadsim('test1_16_02_09.xml',elist);



//WriteSimulation(simfile,elist);
//chdir('..');
//exit();
