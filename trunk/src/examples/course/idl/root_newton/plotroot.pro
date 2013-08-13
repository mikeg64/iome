; here is an example use of the while statement
; which is used for finding the root of a polynomial 
; which is known to lie within a certain interval.
; a is the lower value of the range
; b is the upper value of the range
; This is an example use of the plot function 





function sign, x
    return, (long(x gt 0) - (x lt 0))
end


a = double(0) ;fa = -%inf;
b = double(3)   ;fb = %inf;
x=b;
fa = -double(9.9d99)
fb=double(9.9d99)
n=100

delta=(b-a)/n
xx=dblarr(n)

for i=0,n-1 do begin
	xx[i]=a+double(i)*delta
endfor




eps=double(0.001)

while (sqrt((x-a)^2) gt eps) do begin

  a=x

  fx = 0.5*sin(2*(x-(!pi/4)))+0.5*sin(x);
  dfx= cos(2*(x-(!pi/4)))+0.5*cos(x);
  x=a-(fx/dfx);

endwhile;

print, ' The root is :',x

end
