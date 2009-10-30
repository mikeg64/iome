//xindice functions


//in calling scripts, functions make the following  calls
//  global xiserver;
//  global xiport;
function xhelp()
  
  
  disp('Scilab Xindice help.');
  disp('Define xiserver and xiport as global.');
  disp('global xiserver;');
  disp('global xiport;');
  disp('globalxihost(server,port) to declare global host and port');
  disp('xac(collectionname,newcollection)   add_collection');
  disp('xdc(collection,collectionname)   delete_collection');
  disp('xlcs(collectionname)  list_collections');
  disp('xlc(collectionname)  list_collection');
  disp('xad(collectionname,document,key)  add_document');
  disp('xdd(collectionname,document)   delete_document');
  disp('xpq(collectionname,query)   xpathquery');

  
endfunction

function globalxihost(server,port)
  xiserver=server;
  xiport=port;
endfunction

function [status]=add_collection(server,port,collectionname,newcollection)
  
  scommand=sprintf('xindice add_collection -c xmldb:xindice://%s:%d/db/%s -n %s',server,port,collectionname,newcollection);
  status=unix_g(scommand);
  
endfunction

function [status]=xac(collectionname,newcollection)
  
  status=add_collection(xiserver,xiport,collectioname,newcollection);
endfunction

function [status]=delete_collection(server,port,collection,collectionname)
  
  scommand=sprintf('xindice delete_collection -c xmldb:xindice://%s:%d/db/%s -n %s',server,port,collection,collectionname);
  status=unix_g(scommand);
  
endfunction

function [status]=xdc(collection,collectionname)
   
  status=delete_collection(xiserver,xiport,collection,collectionname);
endfunction

function [result]=list_collections(server,port,collectionname)
  
  scommand=sprintf('xindice list_collections -c xmldb:xindice://%s:%d/db/%s',server,port,collectionname);
  result=unix_g(scommand);
  
endfunction

function [status]=xlcs(collectionname)
  
  status=list_collections(xiserver,xiport,collectionname);
endfunction

function [result]=list_collection(server,port,collectionname)
  
  scommand=sprintf('xindice ld -c xmldb:xindice://%s:%d/db/%s',server,port,collectionname);
  result=unix_g(scommand);
  
endfunction

function [status]=xlc(collectionname)
  
  status=list_collection(xiserver,xiport,collectionname);
endfunction

function [result]=add_document(server,port,collectionname,document,key)
  
  scommand=sprintf('xindice add_document -c xmldb:xindice://%s:%d/db/%s -f %s -n %s',server,port,collectionname,document,key);
  result=unix_g(scommand);
  
endfunction

function [status]=xad(collectionname,document,key)
  
  status=add_document(xiserver,xiport,collectionname,document,key);
endfunction


function [result]=delete_document(server,port,collectionname,document)
  
  scommand=sprintf('xindice dd -c xmldb:xindice://%s:%d/db/%s -n %s',server,port,collectionname,document);
  result=unix_g(scommand);
  
endfunction

function [status]=xdd(collectionname,document)
  
  status=delete_document(xiserver,xiport,collectionname,document);
endfunction


function [result]=xpquery(server,port,collectionname,query)
  
  scommand=sprintf('xindice xpath -c xmldb:xindice://%s:%d/db/%s -q %s',server,port,collectionname,query);
  result=unix_g(scommand);
  
endfunction

function [status]=xpq(collectionname,query)
  
  status=xpquery(xiserver,xiport,collectionname,query);
endfunction
