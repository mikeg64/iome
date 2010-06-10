myftp=ftp('staff.shef.ac.uk','cs1mkg','*******');
cd(myftp,'public_html/uploads');
mget(myftp, 'brain.png');
delete(myftp, 'brain.png');
close(myftp);