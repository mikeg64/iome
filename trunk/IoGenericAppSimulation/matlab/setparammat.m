function [status]=setparammat(name, var, elist)
  %[status]=setparammat(name, var, elist) 
  
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

  [nr,nc]=size(var);
  rvar=reshape(var,nr*nc,1);

  sval=vectostring(rvar',',');
  
  scommand=['iogs setparam mat ',name,' ',sval,' ',num2str(nr),' ',num2str(nc),' ',num2str(id),' ',sport,' ',server];
  %display(scommand);
  status=system(scommand); 

    %status=iosetparammat(obj, id,name,rvar,nr,nc);

  
%endfunction



function status = iosetparammat(obj,id,name,value,nr,nc)
%setparammat(obj,id,name,value,nr,nc)
%
%   Service definition of function ns__setparammat
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (Array)
%       nr = (int)
%       nc = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   value, ...
   nr, ...
   nc, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   'nr', ...
   'nc', ...
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
    'setparammat', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
