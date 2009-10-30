import iome
#myvar=[]
#myvar.append('http://localhost:8080')
#myvar.append('localhost')
#myvar.append(8080)
##myvar.append(0)
#myvec=[]
#myvec.append(0.1)
#myvec.append(0.2)
#myvec.append(0.3)
#iome.AddVecParam('newvec2',myvec,3,7,myvar)

#myvec=iome.GetVecParam('newvec2',3,myvar)
elist=iome.iome('localhost',8080,0);
vam1=iome.getparammat('m1',5,3,elist);

m2=iome.getparammat('m2',5,3,elist)
m1=iome.getparammat('m1',5,3,elist)

m2[0][0]=m1[0][0]
m2[4][2]=m1[4][2]
