import iome
myvar=[]
#myvar.append('http://localhost:8080')
myvar.append('localhost')
myvar.append(8080)
myvar.append(0)

iome.AddIntParam('i1',25,7,myvar)
res=iome.GetIntParam('i1',myvar)
print res;

iome.AddFloatParam('d1',25.123456789,7,myvar)
res=iome.GetFloatParam('d1',myvar)
print res;

iome.AddStringParam('s1','test string',7,myvar)
res=iome.GetStringParam('s1',myvar)
print res;


myvec=[]
myvec.append(0.1)
myvec.append(0.2)
myvec.append(0.3)
iome.AddVecParam('newvec2',myvec,3,7,myvar)

myvec=iome.GetVecParam('newvec2',3,myvar)
print myvec
