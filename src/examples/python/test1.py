import iome
myvar=[]
#myvar.append('http://localhost:8080')
myvar.append('localhost')
myvar.append(8080)
myvar.append(0)

iome.addparamint('i1',25,myvar)
res=iome.getparamint('i1',myvar)
print res;

iome.addparamdouble('d1',25.123456789,myvar)
res=iome.getparamdouble('f1',myvar)
print res;

iome.addparamstring('s1','test string',myvar)
res=iome.getparamstring('s1',myvar)
print res;


myvec=[]
myvec.append(0.1)
myvec.append(0.2)
myvec.append(0.3)
iome.addparamvec('newvec2',myvec,3,myvar)

myvec=iome.getparamvec('newvec2',3,myvar)
print myvec
