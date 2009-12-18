function gendxgen(directory,jobname,nsteps, n1,n2)
 %file=out/jobform.out
  %grid = 1
  %format = ascii
  %interleaving = record
  %majority = row
  %field = nsteps, nx, ny
  %structure = scalar, scalar, scalar
  %type = int, int, int
  %dependency = positions, positions, positions
  %positions = regular, 0, 1

  %end

  dxformgenfile=['dx/',jobname,'_form.general'];
  fdform=fopen(dxformgenfile,'w');
    fprintf(fdform, 'file=%s\n', [directory,'/form',jobname,'.out']);
    fprintf(fdform,'grid=1\n');
    fprintf(fdform,'format = ascii \n interleaving = record \n majority = row \n');
    fprintf(fdform, 'field = nsteps, nx, ny \n structure = scalar, scalar, scalar \n type = int, int, int  \n dependency = positions, positions,positions  \n positions = regular, 0, 1 \n end \n ');
  fclose(fdform);    
%generate dx general file for this data set
  %file=out/job.out
  %grid 51 x 51
  %format = ascii
  %interleaving = field
  %majority = row
  %header = lines 1

  %series =  24 , 1, 1, separator=lines 1
  %field = field0, field1
  %structure = 2-vector, scalar
  %type = float, float
  %dependency = positions, positions
  %positions = regular,regular, 0, 1,0,1

  %end
  dxgenfile=['dx/',jobname,'.general'];

  fdform=fopen(dxgenfile,'w');
    fprintf(fdform, 'file=%s\n', [directory,'/'+jobname,'.out']);
    fprintf(fdform,'grid %d X %d\n',n1,n2);
    fprintf(fdform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    fprintf(fdform, 'series =  %d  , 1, 1, separator=lines 1\n',nsteps-1);
    fprintf(fdform, 'field = field0 \n structure = scalar \n type = float  \n dependency = positions  \n positions = regular,regular,0,1,0,1 \n end \n ');
  fclose(fdform);


 basedxgenfile=['dx/base',jobname,'.general'];

  fdbform=fopen(basedxgenfile,'w');
   % fprintf(fdbform, 'file=%s\n', directory+'/'+jobname+'.out');
    fprintf(fdbform,'grid %d X %d\n',n1,n2);
    fprintf(fdbform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    fprintf(fdbform, 'series =  1  , 1, 1, separator=lines 1\n');
    fprintf(fdbform, 'field = field0\n structure = scalar \n type = float  \n dependency = positions  \n positions = regular,regular,0,1, 0,1 \n end \n ');
  fclose(fdbform);
