myftp=ftp('cpaneldev.shef.ac.uk','cs1mkg','Ambodach1');
cd(myftp,'public_html/iometest/uploads');
mget(myftp, 'brain.png');
%delete(myftp, 'brain.png');
close(myftp);