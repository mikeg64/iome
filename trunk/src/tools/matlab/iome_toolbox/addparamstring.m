function [status]=addparamstring(name, var,elist)
  %AddMetadata(name, property, port) 
  nargin=length(elist);
  flag=7;
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

     status=ioaddparamstring(obj, id,name,var,flag);

%endfunction

function status = ioaddparamstring(obj,id,name,value,iflag)
%addparamstring(obj,id,name,value,iflag)
%
%   Service definition of function ns__addparamstring
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (string)
%       iflag = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   value, ...
   iflag, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   'iflag', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'addparamstring', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
