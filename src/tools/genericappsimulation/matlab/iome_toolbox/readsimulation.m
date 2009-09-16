function [value]=readsimulation(filename,elist)
  %GetMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0 
    server=elist{1};
    if nargin>1 
      port=elist{2};
      if nargin>2 
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
  value=ioreadsimulation(obj,id,filename);
  %return value;
  
 %endfunction



function status = ioreadsimulation(obj,id,filename)
%readsimulation(obj,id,filename)
%
%   Service definition of function ns__readsimulation
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
    'readsimulation', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
