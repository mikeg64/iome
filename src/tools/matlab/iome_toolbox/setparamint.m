function [status]=setparamint(name, var,elist)
  %[status]=setparamint(name, var,elist) 
  
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

  
      status=iosetparamint(obj, id,name,var);

%endfunction


function status = iosetparamint(obj,id,name,value)
%setparamint(obj,id,name,value)
%
%   Service definition of function ns__setparamint
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (int)
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
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setparamint', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
