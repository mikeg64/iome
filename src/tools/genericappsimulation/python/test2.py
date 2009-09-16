import iome
myvar=[]
#myvar.append('http://localhost:8080')
myvar.append('localhost')
myvar.append(8080)
myvar.append(0)
#myvec=[]
#myvec.append(0.1)
#myvec.append(0.2)
#myvec.append(0.3)
#iome.AddVecParam('newvec2',myvec,3,7,myvar)

myvec=iome.GetVecParam('newvec2',3,myvar)
