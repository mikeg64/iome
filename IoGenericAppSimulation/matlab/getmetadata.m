function [property]=getmetadata(name, elist)
  %GetMetadata(name, property, port) 
  
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
  property=iogetmetadata(obj,id,name);
  return property;
  
 %endfunction



function property = iogetmetadata(obj,id,name)
%getmetadata(obj,id,name)
%
%   Service definition of function ns__getmetadata
%   
%     Input:
%       id = (int)
%       name = (string)
%   
%     Output:
%       property = (string)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   };
names = { ...
   'id', ...
   'name', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'getmetadata', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
property = parseSoapResponse(response);
