function value = getparamint(obj,id,name)
%getparamint(obj,id,name)
%
%   Service definition of function ns__getparamint
%   
%     Input:
%       id = (int)
%       name = (string)
%   
%     Output:
%       value = (int)

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
    'getparamint', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
value = parseSoapResponse(response);
