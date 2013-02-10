/*integral_simpson.c*/

/*Integratopin using Simpsons rule*/


#include <stdio.h>
#include <math.h>
#include <float.h>

#define N 100
#define PI 3.1415927

//quadrature to higher order using lagrange interpolation

double testfunction (double x)
{
    double y=sin(x);
    return y;
}

//lagrange interpolation

//xval is the value of x at which we wish to interpolate
//f is the series of values
double lagrange_interp(double xval,double *f, double *x, int i)
{  
    t1=(xval-x[i])*(xval-x[i+1])/((x[i-1]-x[i])*(x[i-1]-x[i+1]));
    t2=(xval-x[i-1])*(xval-x[i+1])/((x[i]-x[i-1])*(x[i]-x[i+1]));
    t3=(xval-x[i-1])*(xval-x[i])/((x[i+1]-x[i-1])*(x[i+1]-x(i)));
    y=t1*f[i-1]+t2*f[i]+t3*f[i+1];
}


int main(int argc, char **argv)
{
	int i;
	double h;
	double y[N];
        double x[N];

	double ydash15p[N];
        double ydash13p[N];
        double yddash15p[N];

     /*Find the derivative of sin (x)*/
        for(i=0;i<N;i++)
        {
		x[i]=2*i*PI/(N-1);
		y[i]=sin(x[i]);	
        }

	h=2*PI/N;

	ydash15p[1]=0;
	ydash15p[2]=0;
	for(i=3;i<=N-2;i++)
	    ydash15p[i]=diff5p(y,i,h);
	
	ydash15p[N-1]=0;
	ydash15p[N]=0;

	ydash13p[1]=0;
	for(i=2;i<N-1;i++)
	    ydash13p[i]=diff3p(y,i,h);
	
	ydash13p[N]=0;


	yddash15p[1]=0;
	yddash15p[2]=0;
	for(i=3;i<=N-2;i++)
	    yddash15p[i]=diffdd5p(y,i,h);
	
	yddash15p[N-1]=0;
	yddash15p[N]=0;

	for(i=0;i<=N-1;i++)
	   printf("%d %g %g %g %g %g %g\n",i,x[i],y[i],ydash13p[i],ydash15p[i],cos(x[i])-ydash13p[i],cos(x[i])-ydash15p[i]);





}
