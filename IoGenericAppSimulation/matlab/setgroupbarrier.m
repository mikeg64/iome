function [value]=setgroupbarrier(name,elist)
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
  value=iosetgroupbarrier(obj,id,state);
  return value;
  
 %endfunction


function newstate = setgroupbarrier(obj,id,state)
%setgroupbarrier(obj,id,state)
%
%   Service definition of function ns__setgroupbarrier
%   
%     Input:
%       id = (int)
%       state = (int)
%   
%     Output:
%       newstate = (int)

% Build up the argument lists.
values = { ...
   id, ...
   state, ...
   };
names = { ...
   'id', ...
   'state', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setgroupbarrier', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
newstate = parseSoapResponse(response);
