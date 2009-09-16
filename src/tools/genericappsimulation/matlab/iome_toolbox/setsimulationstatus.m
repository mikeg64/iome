function [status]=setsimulationstatus(newstatus,elist)
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
  status=iosetsimulationstatus(obj,id,newstatus);
  return status;
  
 %endfunction



function status = iosetsimulationstatus(obj,newstatus,isimid)
%setsimulationstatus(obj,newstatus,isimid)
%
%   Service definition of function ns__setsimulationstatus
%   
%     Input:
%       newstatus = (int)
%       isimid = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   newstatus, ...
   isimid, ...
   };
names = { ...
   'newstatus', ...
   'isimid', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'setsimulationstatus', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
