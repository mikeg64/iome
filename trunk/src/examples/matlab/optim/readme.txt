Using the ftp client failed to run on our local cluster matlab client failed to work
so we used an ftp shell script client

ftp -i cpaneldev.shef.ac.uk < cpanellogin.sh

using batchmode store ftp server information in a file in $HOME called .netrc
the .netrc filehas the follwoing line (or lines)

machine cpaneldev.shef.ac.uk login username passwd thepassword


It is important to set the permissions for .netrc to  600(rw----)

Useful reference   http://rcsg-gsir.imsb-dsgi.nrc-cnrc.gc.ca/documents/internet/node52.html

Start the iome server using the following command
iogs initiome null caiman null 60000 >& iogs.log &
