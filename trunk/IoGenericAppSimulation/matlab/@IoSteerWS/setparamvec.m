function status = setparamvec(obj,id,name,value,n)
%setparamvec(obj,id,name,value,n)
%
%   Service definition of function ns__setparamvec
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (Array)
%       n = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   value, ...
   n, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   'n', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   'Array', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setparamvec', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
