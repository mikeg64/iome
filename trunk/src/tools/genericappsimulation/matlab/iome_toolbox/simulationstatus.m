function [status]=simulationstatus(elist)
  %GetMetadata(name, property, port) 
  
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
  status=iosimulationstatus(obj,id);
  return status;
  
 %endfunction



function status = iosimulationstatus(obj,isimid)
%simulationstatus(obj,isimid)
%
%   Service definition of function ns__simulationstatus
%   
%     Input:
%       isimid = (int)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   isimid, ...
   };
names = { ...
   'isimid', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'simulationstatus', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
