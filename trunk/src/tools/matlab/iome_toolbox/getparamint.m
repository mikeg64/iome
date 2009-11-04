function [value]=getparamint(name,elist)
  %[value]=getparamint(name,elist)
  
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
  value=iogetparamint(obj,id,name);

  
 %endfunction



function value = iogetparamint(obj,id,name)
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
