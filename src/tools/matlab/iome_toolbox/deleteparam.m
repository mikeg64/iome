function [property]=deleteparam(name,elist)
  %GetMetadata(name, property, port) 
  
  nargin=length(elist);
  if nargin>0
    server=elist{1};
    if nargin>1
      port=elist{2};
      if nargin>2
         id= (elist{3});
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
  property=iodeleteparam(obj,name,id);
  
 %endfunction



function status = iodeleteparam(obj,name,id)
%deleteparam(obj,name,id)
%
%   Service definition of function ns__deleteparam
%   
%     Input:
%       name = (string)
%       id = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   name, ...
   id, ...
   };
names = { ...
   'name', ...
   'id', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'deleteparam', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
