function gendxgen(directory,jobname,nsteps, n1,n2)
%generate dx general file 
%describing magnetic fields
%particle locations

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

  dxformgenfile='dx/'+jobname+'_form.general';
  fdform=mopen(dxformgenfile,'w');
    mfprintf(fdform, 'file=%s\n', directory+'/form'+jobname+'.out');
    mfprintf(fdform,'grid=1\n');
    mfprintf(fdform,'format = ascii \n interleaving = record \n majority = row \n');
    mfprintf(fdform, 'field = nsteps, nx, ny \n structure = scalar, scalar, scalar \n type = int, int, int  \n dependency = positions, positions,positions  \n positions = regular, 0, 1 \n end \n ');
  mclose(fdform);    
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
  dxgenfile='dx/'+jobname+'.general';

  fdform=mopen(dxgenfile,'w');
    mfprintf(fdform, 'file=%s\n', directory+'/'+jobname+'.out');
    mfprintf(fdform,'grid %d X %d\n',n1,n2);
    mfprintf(fdform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    mfprintf(fdform, 'series =  %d  , 1, 1, separator=lines 1\n',nsteps-1);
    mfprintf(fdform, 'field = field0, field1 \n structure = 2-vector, scalar \n type = float, float  \n dependency = positions, positions  \n positions = regular,regular, 0, 1,0,1 \n end \n ');
  mclose(fdform);


 basedxgenfile='dx/base'+jobname+'.general';

  fdbform=mopen(basedxgenfile,'w');
   % mfprintf(fdbform, 'file=%s\n', directory+'/'+jobname+'.out');
    mfprintf(fdbform,'grid %d X %d\n',n1,n2);
    mfprintf(fdbform,'format = ascii \n interleaving = field \n majority = row \n header = lines 1 \n');
    mfprintf(fdbform, 'series =  1  , 1, 1, separator=lines 1\n');
    mfprintf(fdbform, 'field = field0, field1 \n structure = 2-vector, scalar \n type = float, float  \n dependency = positions, positions  \n positions = regular,regular, 0, 1,0,1 \n end \n ');
  mclose(fdbform);

