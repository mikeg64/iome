function [value]=getparammat(name,nr,nc,elist)
  %GetMetadata(name, property, port) 
  
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
  vvalue=iogetparammat(name, nr,nc,obj,id);

  value=reshape(vvalue,nr,nc);

  return value;
  
 %endfunction


function dval = iogetparammat(obj,id,name,nr,nc)
%getparammat(obj,id,name,nr,nc)
%
%   Service definition of function ns__getparammat
%   
%     Input:
%       id = (int)
%       name = (string)
%       nr = (int)
%       nc = (int)
%   
%     Output:
%       dval = (Array)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   nr, ...
   nc, ...
   };
names = { ...
   'id', ...
   'name', ...
   'nr', ...
   'nc', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'getparammat', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
dval = parseSoapResponse(response);
