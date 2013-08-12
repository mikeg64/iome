Function Sign, x
    temx = Cast(x,0,5)
    return, long((temx gt 0)) - (temx lt 0)
end



; here is an example use of the while statement
; which is used for finding the root of a polynomial 
; which is known to lie within a certain interval.
; a is the lower value of the range
; b is the upper value of the range

a = 0  ;fa = -%inf;
b = 3   ;fb = %inf;
eps=0.0000001

while (abs(b-a)>(%eps*b)) do begin

  x = (a+b)/2;
  fx = x^3-2*x-5;
  if (sign(fx)eq sign(fa)) then begin
    a = x;
    fa = fx;
  endif else begin
    b = x;
    fb = fx;
  endelse;

endwhile;

print, ' The root is :',x


