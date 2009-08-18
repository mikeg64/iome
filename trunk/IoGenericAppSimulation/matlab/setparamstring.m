function [status]=setparamstring(name, var,elist)
  %AddMetadata(name, property, port) 
  
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

       status=iosetparamstring(obj, id,name,var);

%endfunction


function status = iosetparamstring(obj,id,name,value)
%setparamstring(obj,id,name,value)
%
%   Service definition of function ns__setparamstring
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (string)
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
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setparamstring', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
