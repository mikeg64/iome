Running collaboration demo
Some building tips
iocollabddxwsc
mv to directory 
src/tools/collabdxwebclient

type the following commands
autoheader
configure --prefix /home/username/proj/iodev1 

In the above command make sure directory prefix points to correct path of source distribution
Edit the Makefile check that the variable DXBASE = /usr/lib/dx
is correct and points to the correct location of the IBM data explorer development libraries

make all
 to generate the executable iocollabdxwsc
as root copy this to /usr/bin
Move to the example directory e.g. src/tools/genericappsimulation/scilab/scilab_wave_ws
start the iome server using the command
iogs initiome null mysim null

start scilab and start the wave simulation
or scilab -nb -nw -f steerwave.sce

Start the visualisation
iocollabdxwsc steerwave2d.net 8080 localhost




