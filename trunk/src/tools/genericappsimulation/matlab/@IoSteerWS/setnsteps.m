function nsteps = setnsteps(obj,id,newnsteps)
%setnsteps(obj,id,newnsteps)
%
%   Service definition of function ns__setnsteps
%   
%     Input:
%       id = (int)
%       newnsteps = (int)
%   
%     Output:
%       nsteps = (int)

% Build up the argument lists.
values = { ...
   id, ...
   newnsteps, ...
   };
names = { ...
   'id', ...
   'newnsteps', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setnsteps', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
nsteps = parseSoapResponse(response);
