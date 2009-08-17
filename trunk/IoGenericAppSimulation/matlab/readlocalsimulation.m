function [result]=readlocalsimulation(filename, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
  nargin=length(elist);
  if nargin>0 then
    server=elist{1};
    if nargin>1 then
      port=elist{2};
      if nargin>2 then
         id=elist{3};
      else
         id=0;
      end 
    else
      port=8080;
    end
  else
    server='localhost';
    port=8080;
    id=0;
  end

  sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  %Submit the generic simulation
  %Simulation Config name
  %returns
  fid = fopen(filename, 'r');
  [a,count] = fscanf(fid, '%c', inf);
  fclose(fid);
  
  result=ioreadlocalsimulation(obj,id,a);
  
%endfunction


function status = ioreadlocalsimulation(obj,id,filename)
%readlocalsimulation(obj,id,filename)
%
%   Service definition of function ns__readlocalsimulation
%   
%     Input:
%       id = (int)
%       filename = (string)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   filename, ...
   };
names = { ...
   'id', ...
   'filename', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'readlocalsimulation', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
