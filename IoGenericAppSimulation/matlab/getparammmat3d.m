function [value]=getparammmat3d(name,n,p,q,nr,nc,elist)
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
  vvalue=iogetparammmat3d(name, n,p,q,nr,nc,obj,id);

   
    ind=1;
    for i1=1:ni
       for i2=1:nj
          for i3=1:nk
            for i=1:nr
              for j=1:nc
               value(i1,i2,i3,i,j)=vvalue(ind);
               ind=ind+1;
              end
            end
        end
      end
    end


  return value;
  
 %endfunction


function mmat3d = iogetparammmat3d(obj,id,name,n,p,q,nr,nc)
%getparammmat3d(obj,id,name,n,p,q,nr,nc)
%
%   Service definition of function ns__getparammmat3d
%   
%     Input:
%       id = (int)
%       name = (string)
%       n = (int)
%       p = (int)
%       q = (int)
%       nr = (int)
%       nc = (int)
%   
%     Output:
%       mmat3d = (Array)

% Build up the argument lists.
values = { ...
   id, ...
   name, ...
   n, ...
   p, ...
   q, ...
   nr, ...
   nc, ...
   };
names = { ...
   'id', ...
   'name', ...
   'n', ...
   'p', ...
   'q', ...
   'nr', ...
   'nc', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'getparammmat3d', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
mmat3d = parseSoapResponse(response);
