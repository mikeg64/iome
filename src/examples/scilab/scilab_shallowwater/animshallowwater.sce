
// Display mode
mode(0);

// Display warning for floating point exception
ieee(1);



// !! L.3: Matlab function figure not yet converted, original calling sequence used.
figure(1)

//Animation of H wave propogating
// ! L.6: mtlb(t) can be replaced by t() or t whether t is an M-file or not.

for index = 1:max(size(mtlb_double(mtlb(t))))
  // ! L.7: mtlb(x) can be replaced by x() or x whether x is an M-file or not.
  // ! L.7: mtlb(y) can be replaced by y() or y whether y is an M-file or not.
  // ! L.7: mtlb(h) can be replaced by h() or h whether h is an M-file or not.
  // !! L.7: Unknown function h not converted, original calling sequence used.
  // !! L.7: Matlab function mesh not yet converted, original calling sequence used.
  mesh(mtlb(x),mtlb(y),h(":",":",index))
  set(gca(),"data_bounds",matrix([0,100000,0,100000,4990,5010],2,-1))
  title("AERSP 423 Computer Project Part II")
  xlabel("X Domain [m]")
  ylabel("Y Domain [m]")
  zlabel("Height [m]")
  xpause(1000*0.02)
end;
