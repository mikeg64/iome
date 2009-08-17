function [result]=newsimulation(simname,xslname, elist)
%function [status]=InitIOME(simname, configname, statename,port,server)
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
  %Submit the generic simulation
  %Simulation Config name
  %returns
  
  
  result=ionewsimulation(obj,simname,xslname,isimid);
  
%endfunction




function status = ionewsimulation(obj,id,simname,xslname)
%newsimulation(obj,id,simname,xslname)
%
%   Service definition of function ns__newsimulation
%   
%     Input:
%       id = (int)
%       simname = (string)
%       xslname = (string)
%   
%     Output:
%       status = (int)

% Build up the argument lists.
values = { ...
   id, ...
   simname, ...
   xslname, ...
   };
names = { ...
   'id', ...
   'simname', ...
   'xslname', ...
   };
types = { ...
   '{http://www.w3.org/2001/XMLSchema}int', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };

% Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'urn:IoSteerWS', ...
    'newsimulation', ...
    values,names,types,'rpc');
response = callSoapService( ...
    obj.endpoint, ...
    '', ...
    soapMessage);
status = parseSoapResponse(response);
