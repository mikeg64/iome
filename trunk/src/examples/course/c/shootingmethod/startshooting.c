
/*PROGRAM STARTSHOOTING
  THIS PROVIDES A SOLUTION FOR A BOUNDARY-VALUE PROBLEM FOR A
  FIRST-ORDER ODE WITH ONE UNKNOWN PARAMETER TO BE DETERMINED.
  THE ODE IS OF THE FORM     Dy/Dx = f(x,Q)  WHERE Q IS THE 
  UNKNOWN PARAMETER.   THE BOUNDARY CONDITIONS ARE y = Ya FOR
  x = a AND y = Yb FOR X = b.   
  THE FUNCTION f(x,Q) IS PROVIDED AS A FUNCTION STATEMENT.*/
#include <stdio.h>
#include <math.h>
/*Parkers fluid solar wind model*/
double fun(r,u)
{
        double G=6.67*pow(10,-11);
        double M=2*pow(10,30);
        double cs=sqrt(2*1.38*pow(10,-23)*4*pow(10,4)/(1.67*pow(10,-27))); /*sqrt(2kT/m)*/
        double dudr;
        
        dudr=(u/r)*(2-(G*M/(cs*cs*r)))/((u/cs)*(u/cs)-1);
        
        return dudr;
	//return (-15.915494*q/pow((2-x),2));
}

void main(int argc, char **argv)
{
	double y[1000],dy[4];
        double xi,xf,yf,q,h;
        double w[4]={0.0,0.5,0.5,1.0};
	char ans;

        int n;
        printf("INPUT THE FIRST BOUNDARY CONDITION AS a Ya\n");
        printf("WHERE y = Ya WHEN x = a.\n");
        scanf("Input a ya?\n", &xi, &y[0]);

        printf("INPUT THE SECOND BOUNDARY CONDITION AS b Yb\n");
        printf("WHERE y = Yb WHEN x = b.\n");
        scanf("Input b yb?\n", &xf, &yf);

	printf(" INPUT THE INTEGRATION STEP LENGTH h IN THE \n");
	printf(" FORM OF AN INTEGER N WHERE h = [b - a]/N. \n");
	printf(" IF YOU WANT OUTPUT OF Y AT INTERVALS OF [B-A]/M\n");
	printf(" THEN MAKE N A MULTIPLE OF M.\n");

        scanf("input n?\n",&n);
        h=(xf-xi)/n;

        scanf("input estimated unknown parameter?\n",&q);


}

