function obj = IoSteerWS

obj.endpoint = 'http://mikeg.staff.shef.ac.uk/IOSteerWS.cgi';
obj.wsdl = 'file:///home/cs1mkg/proj/iome2_2_1/IoGenericAppSimulation/matlab/../../IoSimulation/IoSteerWS.wsdl';

obj = class(obj,'IoSteerWS');

