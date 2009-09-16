function status = setparamdouble(obj,id,name,value)
%setparamdouble(obj,id,name,value)
%
%   Service definition of function ns__setparamdouble
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (double)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   value, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}double', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setparamdouble', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
