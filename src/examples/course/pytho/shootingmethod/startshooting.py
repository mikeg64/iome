from numpy import *
from os import *
from math import *


import numpy as np


#shooting method example using python

#      PROGRAM STARTSHOOTING
#  THIS PROVIDES A SOLUTION FOR A BOUNDARY-VALUE PROBLEM FOR A
#  FIRST-ORDER ODE WITH ONE UNKNOWN PARAMETER TO BE DETERMINED.
#  THE ODE IS OF THE FORM     Dy/Dx = f(x,Q)  WHERE Q IS THE 
#  UNKNOWN PARAMETER.   THE BOUNDARY CONDITIONS ARE y = Ya FOR
#  x = a AND y = Yb FOR X = b.   
#  THE FUNCTION f(x,Q) IS PROVIDED AS A FUNCTION STATEMENT.

y=zeros(1000)
w=zeros(4)
dy=zeros(4)

w=[0.0,0.5,0.5,1.0]

print 'INPUT THE FIRST BOUNDARY CONDITION a,Ya'
print 'WHERE y = Ya WHEN x = a.'

xi=input('a')
y[0]=input('Ya')

print 'INPUT THE FINAL BOUNDARY CONDITION  b,Yb'
print 'WHERE y = Yb WHEN x = b.'
xf=input('b')
yf=input('Yb')

print' INPUT THE INTEGRATION STEP LENGTH h IN THE '
print' FORM OF AN INTEGER N WHERE h = [b - a]/N. '
print' IF YOU WANT OUTPUT OF Y AT INTERVALS OF [B-A]/M'
print' THEN MAKE N A MULTIPLE OF M.'


n=input('n')
h=(xf-xi)/n

q=input('INPUT ESTIMATE OF THE UNKNOWN PARAMETER, Q.')

def f(x,q):
    f=-15.915494*q/(math.pow(2-x,2))
    return f

for x in i[1:n]:
    x=(i-1)*h
    if x < 0: a.remove(x)

#  THE RUNGE-KUTTA INTEGRATION NOW BEGINS.F
      DO 1 I=1,N
      X=(I-1)*H
      DO 2 J=1,4
      XX=X+W(J)*H
      DY(J)=H*FUN(XX,Q)
    2 CONTINUE
      Y(I)=Y(I-1)+(DY(1)+DY(4)+2*(DY(2)+DY(3)))/6.0
    1 CONTINUE
      WRITE(6,100)Y(N)
  100 FORMAT(20H THE VALUE OF Yb IS ,F8.2)
    5 WRITE(6,'('' OUTPUT INTERMEDIATE VALUES OF Y? [Y/N]'')')
      READ(5,50)ANS
   50 FORMAT(A1)           
      IF(ANS.EQ.'Y'.OR.ANS.EQ.'y')GOTO 3
      IF(ANS.EQ.'N'.OR.ANS.EQ.'n')GOTO 4
      GOTO 5
    3 WRITE(6,'('' DO YOU WANT PRINTED OUTPUT? [Y/N]'')')
      READ(5,50)ANS
      IF(ANS.EQ.'Y'.OR.ANS.EQ.'y')THEN
      IOUT=9
      OPEN(UNIT=9, FILE='mydoc.txt')
      GOTO 7
      ENDIF
      IF(ANS.EQ.'N'.OR.ANS.EQ.'n')THEN
      IOUT=6
      GOTO 7
      ENDIF
      GOTO 3
    7 WRITE(6,'('' INPUT M WHERE OUTPUT INTERVALS ARE H*N/M '')')
      READ(5,*)M
      K=N/M
      DO 6 I=0,N,K
      XX=I*H
      WRITE(IOUT,200)XX,Y(I)
  200 FORMAT(F6.3,2X,F8.2)
    6 CONTINUE
    4 STOP
 END PROGRAM STARTSHOOTING

 FUNCTION myfunc1(x,q)	! external procedure to swap two reals

  IMPLICIT NONE
  REAL, INTENT (IN):: x,q
  REAL :: myfunc1
   myfunc1=  -15.915494*q/(2-x)**2

 
END FUNCTION myfunc1
