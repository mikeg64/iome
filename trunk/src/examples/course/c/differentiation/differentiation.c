/*differentitation.c*/

/*Example of arrays and function calls*/

/*Improve the code  by making bound checkers*/
/*Verify that second derivative is -sin(x)
  what are the errors for the 3 point and 5 point methods*/

/*Using 3 and 5 point functions to compute derivatives*/

/*3 and 5 point functions to compute derivatives
 need to use extrapolation to determine derivative at boundary*/


#include <stdio.h>
#include <math.h>
#include <float.h>

#define N 100
#define PI 3.1415927

float sign(float f){return(fabs(f)/f);}

double diff5p( double *y,int i,double h)
{
    double diff5p;
    diff5p=(y[i-2]-8*y[i-1]+8*y[i+1]-y[i+2])/(12*h);
    return diff5p;
}

double diff3p( double *y,int i,double h)
{
    double diff3p;
    diff3p=(y[i+1]-y[i-1])/(2*h);
    return diff3p;
}

double diffdd5p( double *y,int i,double h)
{
    double diffdd5p;
    diffdd5p=(-y[i-2]+16*y[i-1]+16*y[i+1]-y[i+2]-30*y[i])/(12*h*h);
    return diffdd5p;
}

double diffdd3p( double *y,int i,double h)
{
    double diffdd3p;
    diffdd3p=(y[i+1]+y[i-1]-2*y[i])/(h*h);
    return diffdd3p;
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
