function [status]=addparamvec(name, var,elist)
  %[status]=addparamvec(name, var, flag,elist) 
  flag=7;
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

  %status=ioaddparamvec(obj, id,name,var,vsize,flag);
   vsize=length(var);
   sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  sval=vectostring(var',',');
  
  scommand=['iogs addparam vec ',name,' ',sval,' ',num2str(vsize),' ',num2str(flag),' ',num2str(id),' ',sport,' ',server];
  %display(scommand);
  system(scommand);



%endfunction



function status = ioaddparamvec(obj,id,name,value,n,iflag)
%addparamvec(obj,id,name,value,n,iflag)
%
%   Service definition of function ns__addparamvec
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (Array)
%       n = (int)
%       iflag = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   value, ...
   n, ...
   iflag, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   'n', ...
   'iflag', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   'Array', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'addparamvec', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
