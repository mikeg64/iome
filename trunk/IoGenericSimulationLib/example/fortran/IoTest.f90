      program iotestf90
!      include "IoTest.h"

      integer*2 i1,port,id
      character*12 server
      character*4 name
      character*1 null
      null=char(0)
      i1=0
      port=8080
      id=0
      server="localhost"//null
      name="i1"//null
!      print * ,'in fortan:',  server  

!     getintparam_( int id,char *sname,int *iv,  int port, char *sserver );
      call getintparam( id,name,i1,  port, server )	

      print *, '   i1 is ', i1
      
      end
      

