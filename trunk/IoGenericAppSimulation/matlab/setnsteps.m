function [newnsteps]=setnsteps(var,elist)
   
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
  
  newnsteps=iosetnsteps(obj,id,var);
%endfunction


function nsteps = iosetnsteps(obj,id,newnsteps)
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
