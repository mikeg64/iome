1. Metadata generation 
2. Xindice db query using xpath gui form provided
3. Steering
4. Simulation as a service
5. Normal visualisation
6. Collaborative visualisation


Starting a job for collaborative visualisation

generating the data
1. start server iogs initiome null mysim null
2. adjust paramstest1.sce (job name i.e. metadata prop called name)
3. run scilab with test1.sce
4. run dx visualisation with shallowwater.net
4. generates simfile which maybe reloaded can be run using test2.sce

collaborative visulisation
1. Use the following files for dx shallowwatercollab.net,shallowwatercollab.cfg requires the output data using mysim.xml
dx can be started initially without the use of collborative mode
2. Start the collaboration server iogs initiome null mysim null 8080
3. Followoing files required collabtest1.sce,iocollabshallowwater.sce and paramscollabtest1.sce
4. Load the collaboration server with initial data/parameters e.g. using scilab as follows
(could use a python version) scilab -nb -nw -f collabtest1.sce
5. collabtest1.sce so that parameters from previous simulation session may be loaded or by creating a new session
6. Using the version of collabdxwebclient compiled using dxwebclient2
Start iocollabdxwebclient shallowwatercollb.net port localhost 
