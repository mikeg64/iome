#include <stdio.h>
#include <math.h>
#include <float.h>

#define N 100
#define PI 3.1415927

#ifdef USE_GSL
        /*
          gcc -Wall -I/usr/local/include -c example.c
          gcc -L/usr/local/lib example.o -lgsl -lgslcblas -lm
	*/
	#include <gsl/gsl_math.h>
	#include <gsl/gsl_sf_bessel.h>
#endif
#ifdef USE_NAG

#endif


/*function [tdl]=tdl(u1,u2,r1,r2,l,k)
   //calculate phase shift of partial waves tand deltl
   kk=(r1*u1)/(r2*u2);
 tdl=(kk*besselj(l,k*r1)-besselj(l,k*r2))/(kk*bessely(l,k*r1)-bessely(l,k*r2));
endfunction*/

double tdl(double u1,double u2,double r1,double r2,int l,int k)
{
 //calculate phase shift of partial waves tand deltl
   kk=(r1*u1)/(r2*u2);

#ifdef USE_GSL
 tdlv=(kk*gsl_sf_bessel_Jn(l,k*r1)-gsl_sf_bessel_Jn(l,k*r2))/(kk*gsl_sf_bessel_Jn(l,k*r1)-gsl_sf_bessel_Jn(l,k*r2));

#endif
#ifdef USE_NAG
 tdlv=(kk*gsl_sf_bessel_Jn(l,k*r1)-gsl_sf_bessel_Jn(l,k*r2))/(kk*gsl_sf_bessel_Jn(l,k*r1)-gsl_sf_bessel_Jn(l,k*r2));

#endif
	return tdlv;
}



/*//u
function [u]=u(l,r)
  alpha=6.12;
  e=3;
  C=sqrt(e*alpha/25)
  u=exp( (-1)*C*r^(-5));
endfunction*/

double u(int l, double r)
{
  double alpha=6.12;
  double e=3;
  double C=sqrt(e*alpha/25)
  double uv=exp( (-1)*C*pow(r,-5));
   return uv;
}



/*function [v]=v(r,sigma,epsilon)
   //epsilon=5.9;//meV H-Kr interaction
  //sigma=3.57;//Angstrom
  v=10*epsilon*( (sigma/r)^12-2*(sigma/r)^6);
endfunction*/

double v(double r, double sigma, double epsilon)
{
   //epsilon=5.9;//meV H-Kr interaction
  //sigma=3.57;//Angstrom
  vv=10*epsilon*(    (  pow((sigma/r),12)  )-2*(  pow((sigma/r),6)  )       );
    return vv;
}




/*function [f]=f(l,r,e,sigma,epsilon)
  //ra=r*(10^(-10));
  f=v(r,sigma,epsilon)+(hb^2/(2*m*r^2))-e;
endfunction*/

double f(int l, double r, double e,double sigma,double epsilon)
{
	fv=v(r,sigma,epsilon)+((hp*hb)/(2*m*(r*r)))-e;
	return fv;
}


//solve radial wave equation using numerov 
//predictor method to fourth order 
//for 2nd order de's

/*function [numerov]=numerov(u1,u2,l,r,delta,e,sigma,epsilon)

  num1=1/(1-(delta^2/12)*f(l,r+delta,e,sigma,epsilon));
  bracket1=2*u2-u1+(delta^2/12)*(10*f(l,r,e,sigma,epsilon)*u2+f(l,r,e,sigma,epsilon)*u1);
  numerov=num1*bracket1;

endfunction*/

double numerov(double u1,double u2,double l,double r,double delta,double e,double sigma,double epsilon)
{
//solve radial wave equation using numerov 
//predictor method to fourth order 
//for 2nd order de's

  double num1=1/(1-(delta^2/12)*f(l,r+delta,e,sigma,epsilon));
  double bracket1=2*u2-u1+((delta*delta)/12)*(10*f(l,r,e,sigma,epsilon)*u2+f(l,r,e,sigma,epsilon)*u1);
  double numerovv=num1*bracket1;

   return numerovv;
}





int main(int argc, char **argv)
{
deltah=0.01;
nsteps=200;
global m
global hb
//m=938*10^9;
m=1.672*10^(-27);
//hb=6.59*10^(-13);
hb=1.054*10^(-34);
lupper=10
e=1.6*10^(-19);
 
 delta=0.1*(10^(-10));
 
 delta=0.5;
 m=1;
 hb=1;
 e=1;

//2m/hb^2=6.12meV^-1(sigma)^-2
  lupper=10;
  sumdelta=0;
  nr=100;
  ne=250;
  
  sumouter=zeros(ne);
  totsum=0;
  //sigma=0;
  
  u1=zeros(nr,lupper+1);
  u2=zeros(nr,lupper+1);
  u3=zeros(nr,lupper+1);
  //outer loop integration over r
    epsilon=5.9;//meV H-Kr interaction
  sigma=3.57;//Angstrom

  for nec=1:ne
    e=nec*0.0005;
    k=sqrt(2*m*e)/hb;
    totsum=0;
  //sigma=0;
  
  u1=zeros(nr,lupper+1);
  u2=zeros(nr,lupper+1);
  u3=zeros(nr,lupper+1);
  for j=1:nr,
    
    u1=0;
    //inner loop summation over l
    sumdelta=0;
    for i=0:lupper,   
      if j == 1 then
        u1(j,i+1)=.1;
        u2(j,i+1)=delta^(i+1);
      else
        u2(j,i+1)=u3(j-1,i+1);
        u1(j,i+1)=u2(j-1,i+1);
      end;
      
      u3(j,i+1)=numerov(u1(j,i+1),u2(j,i+1),i,3.1+j*delta,delta,e,sigma,epsilon);
      //res=tdl(u1(j,i+1),u2(j,i+1),j*delta,(j+1)*delta,i,k);
      //cosecdelta2=((1/(res^2))+1);
      //sumdelta=sumdelta+(2*i+1)*(1/cosecdelta2); 
    end
    //sumouter(j)=((4*%pi)/(k^2))*sumdelta;
    //totsum=totsum+sumouter(j);
  end
  
 
     for i=0:lupper,   
 
      
       res=tdl(u2(nr-2,i+1),u2(nr-1,i+1),(nr-1)*delta,(nr)*delta,i,k);
      cosecdelta2=((1/(res^2))+1);
      sumdelta=sumdelta+(2*i+1)*(1/cosecdelta2); 
    end
    sumouter(nec)=((4*%pi)/(k^2))*sumdelta;
    totsum=totsum+sumouter(nec);
    
  end
  
  plot(sumouter);


}
