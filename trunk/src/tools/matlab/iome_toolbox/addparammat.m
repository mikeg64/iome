function [status]=addparammat(name, var,elist)
  %[status]=addparammat(name, var,flag,elist) 
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

  [nr,nc]=size(var);
  rvar=reshape(var,nr*nc,1);
  %status=(obj, id,name,rvar,nr,nc,flag);

 %   ind=1;
 % for i=1:nr
 %   for j=1:nc
 %    vvar(ind)=var(i,j);
 %    ind=ind+1;
%    end
%  end


  sval=vectostring(rvar',',');
  
  scommand=['iogs addparam mat ',name,' ',sval,' ',num2str(nr),' ',num2str(nc),' ',num2str(flag),' ',num2str(id),' ',sport,' ',server];
  %display(scommand);
  system(scommand);
  status=0;

    %status=ioaddparammat(obj, id,name,rvar,nr,nc,flag);

%endfunction


function status = ioaddparammat(obj,id,name,value,nr,nc,iflag)
%addparammat(obj,id,name,value,nr,nc,iflag)
%
%   Service definition of function ns__addparammat
%   
%     Input:
%       id = (int)
%       name = (string)
%       value = (Array)
%       nr = (int)
%       nc = (int)
%       iflag = (int)
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
   iflag, ...
   };
names = { ...
   'id', ...
   'name', ...
   'value', ...
   'nr', ...
   'nc', ...
   'iflag', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   'Array', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'addparammat', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
