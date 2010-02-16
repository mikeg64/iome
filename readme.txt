iome installation



To install a binary distribution under linux

1. Install python e.g. http://www.python.org/download/releases/2.5.2/
2. Install scilab http://www.scilab.org/
3. Copy the directory iome_toolbox from src/tools/scilab to the scilab contributions 
  folder.
4. Start scilab and run the builder.sce for the iome_toolbox
5. Copy the iome examples to your home area
6. move to the folder examples/scilab/scilab_wave_ws  run the steer.sh example or windows users
should double click the startdemo.bat file

The following procedure applies for a root user installing iome in the /usr/local directory

change directory to /usr/local
Download the correct binary distribution (e.g. by visiting the project web site or using wget as follows) sudo wget http://iome.googlecode.com/files/iorel1_bin_linux_ubuntu_amd64.tgz.gz
Extract the distribution using sudo tar -zxvf  iorel1_bin_linux_ubuntu_amd64.tgz.gz
sudo mv ioubuntulin_bin_amd64 iome
cd iome
sudo cp iome.sh /etc/profile.d
The iome.sh contains the following lines

#Configure environment to use IOME
export IOME_HOME=”/usr/local/iome”
export PATH=$PATH”:$IOME_HOME/bin”
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH”:$IOME_HOME/lib:$IOME_HOME/bin”
The procedure is easily adapted for use installation in the home area. The distribution does not yet contain the iome.sh script which will be generalised for windows and other linux ditributions and also for final installation of the source distribution.


To install the source version
The Apache Xerces-c and Xalan-C libraries are required
Apache Xerces-c may be downloaded from
http://xerces.apache.org/xerces-c/download.cgi

Apache Xalanc may be downloaded from
http://xml.apache.org/xalan-c/

On ubuntu xercesc is installed using
apt-get install libxerces-c28
apt-get install libxalan110

 
The default version for the xerces libraries is xercesc_2_8 a different version may be selected 
using the XERCESCVERSION flag in the ./configure command
Run the configure routine using
./configure --prefix=/usr/local/iome XERCESCVERSION=xercesc_2_7
make all
make install

For further information refer to the iome blog and wiki


