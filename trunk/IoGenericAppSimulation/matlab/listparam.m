function list = listparam(obj,type,id)
%listparam(obj,type,id)
%
%   Service definition of function ns__listparam
%   
%     Input:
%       type = (string)
%       id = (int)
%   
%     Output:
%       list = (string)

% Build up the argument lists.
values = { ...
   type, ...
   id, ...
   };
names = { ...
   'type', ...
   'id', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'listparam', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
list = parseSoapResponse(response);
