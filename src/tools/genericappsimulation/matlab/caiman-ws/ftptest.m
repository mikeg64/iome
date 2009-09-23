myftp=ftp('cpaneldev.shef.ac.uk','cs6grid','******');
cd(myftp,'public_html/iometest/uploads');
mget(myftp, 'brain.png');
%delete(myftp, 'brain.png');
close(myftp);