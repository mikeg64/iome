
/*PROGRAM STARTSHOOTING
  THIS PROVIDES A SOLUTION FOR A BOUNDARY-VALUE PROBLEM FOR A
  FIRST-ORDER ODE WITH ONE UNKNOWN PARAMETER TO BE DETERMINED.
  THE ODE IS OF THE FORM     Dy/Dx = f(x,Q)  WHERE Q IS THE 
  UNKNOWN PARAMETER.   THE BOUNDARY CONDITIONS ARE y = Ya FOR
  x = a AND y = Yb FOR X = b.   
  THE FUNCTION f(x,Q) IS PROVIDED AS A FUNCTION STATEMENT.*/
#include <stdio.h>
#include <math.h>


double fun(x,q)
{
	return (-15.915494*q/pow((2-x),2));
}

void main(int argc, char **argv)
{
	double y[1000],dy[4];
        double x,xx,xi,xf,yf,q,h;
        double w[4]={0.0,0.5,0.5,1.0};
	char ans;
	FILE *fd;

        int i,j,n,k,m;
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


        /*THE RUNGE-KUTTA INTEGRATION NOW BEGINS.F*/
        for(i=1;i<n;i++)
        {
		x=(i-1)*h;
		for(j=0;j<4;j++)
		{
			xx=x+h*w[j];
			
                        dy[j]=h*fun(xx,q);
		}
		y[i]=y[i-1]+(dy[0]+dy[3]+2*(dy[1]+dy[2]))/6.0;
	}

        scanf("Input m where output intervals are h*n/m?\n",&m);
        k=n/m;
        fd=fopen("mydoc.txt","w");
        for(i=0; i<n;i+=k)
        {
		x=i*h;
                fprintf(fd,"%f %f\n",x,y[i]);
        }
        fclose(fd);

	return;
}

