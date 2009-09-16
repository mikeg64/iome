<<<<<<< .mine
//To use these functions make sure the location of the IOME iogs application
//is on the path
//Linux export IOME_HOME=PATHTOIOME
//Linux export PATH=$PATH":$IOME_HOME/bin"
//Windows set IOME_HOME=PATHTOIOME
//Windows set PATH=%PATH%;$IOME_HOME/bin


//senv_iome_home=getenv('IOME_HOME');
senv_iome_home='/home/mike/proj/iome2_2_1';
apath=sprintf('%s/bin',senv_iome_home);
//set the path
path=getenv('PATH');

newpath=sprintf('%s:%s',path,apath);
setenv('PATH',newpath);

exec(sprintf('%s/IoGenericAppSimulation/scilab/IoGenericScilabSimulation.sce',senv_iome_home));
//exec(sprintf('%s/IoGenericAppSimulation/IoindiceScilabSim.sce',senv_iome_home));
=======
//To use these functions make sure the location of the IOME iogs application
//is on the path
//Linux export IOME_HOME=PATHTOIOME
//Linux export PATH=$PATH":$IOME_HOME/bin"
//Windows set IOME_HOME=PATHTOIOME
//Windows set PATH=%PATH%;$IOME_HOME/bin


senv_iome_home=getenv('IOME_HOME');
//senv_iome_home='/home/mike/proj/iome2_2_1';
//senv_iome_home='C:\Documents and Settings\cs1mkg\My Documents\proj\iome2_2_1';
//apath=sprintf('%s\bin',senv_iome_home);
//set the path
//path=getenv('PATH');

//newpath=sprintf('%s:%s',path,apath);
//newpath=sprintf('%s;%s',path,apath);
//setenv('PATH',newpath);

exec(sprintf('%s/IoGenericAppSimulation/scilab/IoGenericScilabSimulation.sce',senv_iome_home));
//exec(sprintf('%s/IoGenericAppSimulation/IoindiceScilabSim.sce',senv_iome_home));
>>>>>>> .r45
