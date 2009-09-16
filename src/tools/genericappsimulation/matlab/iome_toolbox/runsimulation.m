function [simid]=runsimulation(filename,elist)
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

  fid = fopen(filename, 'r');
  [a,count] = fscanf(fid, '%c', inf);
  fclose(fid);

    sport=sprintf('%d',port);
  obj.endpoint=['http://',server,':',sport];
  simid=iorunsimulation(obj,id,a);
  return simid;
  
 %endfunction




function result = iorunsimulation(obj,id,simfilecontent)
%runsimulation(obj,id,simfilecontent)
%
%   Service definition of function ns__runsimulation
%   
%     Input:
%       id = (int)
%       simfilecontent = (string)
%   
%     Output:
%       result = (string)

% Build up the argument lists.
values = { ...
   id, ...
   simfilecontent, ...
   };
names = { ...
   'id', ...
   'simfilecontent', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'runsimulation', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
result = parseSoapResponse(response);
