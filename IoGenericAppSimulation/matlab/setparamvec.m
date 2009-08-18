function [status]=setparamvec(name, value, n,elist)
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
  sval=vectostring(value',',');
  
  scommand=['iogs setparam vec ',name,' ',sval,' ',num2str(n),' ',num2str(id),' ',sport,' ',server];
  display(scommand);
  system(scommand);
%cvalue=vec2cellarray(value);

%status=iosetparamvec(obj,id,name,cvalue,n);
  status=0;
   
   
   
%endfunction

function status = iosetparamvec(obj,id,name,value,n)
%setparamvec(obj,id,name,value,n)
%
%   Service definition of function ns__setparamvec
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (Array)
%       n = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   value, ...
   n, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   'n', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   'Array', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setparamvec', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
