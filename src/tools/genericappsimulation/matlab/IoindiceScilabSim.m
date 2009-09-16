//xindice functions
function [status]=add_collection(server,port,collectionname,newcollection)
  
  scommand=sprintf('xindice add_collection -c xmldb:xindice://%s:%d/db/%s -n %s',server,port,collectionname,newcollection);
  status=unix_g(scommand);
  
endfunction


function [status]=delete_collection(server,port,collection,collectionname)
  
  scommand=sprintf('xindice delete_collection -c xmldb:xindice://%s:%d/db/%s -n %s',server,port,collection,collectionname);
  status=unix_g(scommand);
  
endfunction

function [result]=list_collections(server,port,collectionname)
  
  scommand=sprintf('xindice list_collections -c xmldb:xindice://%s:%d/db/%s',server,port,collectionname);
  result=unix_g(scommand);
  
endfunction


function [result]=add_document(server,port,collectionname,document,key)
  
  scommand=sprintf('xindice add_document -c xmldb:xindice://%s:%d/db/%s -f %s -n %s',server,port,collectionname,document,key);
  result=unix_g(scommand);
  
endfunction
