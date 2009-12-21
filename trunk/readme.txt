iome installation

1. Install python e.g. http://www.python.org/download/releases/2.5.2/
2. Install scilab http://www.scilab.org/
3. Copy the directory iome_toolbox from src/tools/scilab to the scilab contributions 
  folder.
4. Start scilab and run the builder.sce for the iome_toolbox
5. Copy the iome examples to your home area
6. move to the folder examples/scilab/scilab_wave_ws  run the steer.sh example or windows users
should double click the startdemo.bat file

For further information refer to the iome blog and wiki

To install the source version
The Apache Xerces-c and Xalan-C libraries are required
Apache Xerces-c may be downloaded from
http://xerces.apache.org/xerces-c/download.cgi

Apache Xalanc may be downloaded from
http://xml.apache.org/xalan-c/

On ubuntu xercesc is installed using
apt-get install libxerces-c28
apt-get install libxalan110

 
The default version for the xerces libraries is xercesc_2_8 a diffrenet version may be selected 
using the XERCESCVERSION flag in the ./configure command
Run the configure routine using
./configure --prefix=/usr/local/iome XERCESCVERSION=xercesc_2_7
make all
make install

