/* $Revision: 1.10.6.4 $ */
/*=================================================================
 * revord.c 
 * example for illustrating how to copy the string data from MATLAB
 * to a C-style string and back again
 *
 * takes a row vector string and returns a string in reverse order.
 *
 * This is a MEX-file for MATLAB.
 * Copyright 1984-2006 The MathWorks, Inc.
 *=============================================================*/
#include "mex.h"
#include "soapH.h"

void addparamvec_mex(char *server, mwSize serverlen, char *output_buf)
{
  mwSize i;

  if (serverlen == 0) return;

  int n=3;
  double vv[3];
  for(int i=0; i<3; i++)
      vv[i]=i+0.1;
  int id=0;
  
   
  
  /* reverse the order of the input string */
  for(i=0;i<serverlen-1;i++) 
    *(output_buf+i) = *(server+serverlen-i-2);
  
  
	char m_serverclient[300] = "localhost:8080";
	struct soap m_soapclient;

	int status=0;
	int isize=3;
	double *darray;
	char *name="v1";
    int port=8080;
    int iflag=7;
		
	int size=n;
	float fv;
	int ind=0;

	//the array of floats is string consisting of a comma separated list
	//with no white space


	//if(server != NULL)
	//	sprintf(m_serverclient,"%s:%d",server,port);
	//else
		sprintf(m_serverclient,"%s:%d","localhost",port);
			
	struct fdata thedata;
	thedata.__ptr=vv;
	thedata.__size=n;

	//soap_call_ns__addparamint(&m_soapclient, m_serverclient, "", name, dvalue, iflag, &status );
	//soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", id, name, thedata,n,iflag,&status );
	//soap_call_ns__addparamvec(&m_soapclient, m_serverclient, "", 0, "v1", thedata,3,7,&status ); 
  soap_call_ns__addparamstring(&m_soapclient, m_serverclient, "", 0, "s1", "string",7,&status ); 
  
  
}

void mexFunction( int nlhs, mxArray *plhs[],
                  int nrhs, const mxArray *prhs[])
{
    char *server, *output_buf;
    mwSize buflen;
    
    /* check for proper number of arguments */
    if(nrhs!=1) 
      mexErrMsgTxt("One input required.");
    else if(nlhs > 1) 
      mexErrMsgTxt("Too many output arguments.");

    /* input must be a string */
    if ( mxIsChar(prhs[0]) != 1)
      mexErrMsgTxt("Input must be a string.");

    /* input must be a row vector */
    if (mxGetM(prhs[0])!=1)
      mexErrMsgTxt("Input must be a row vector.");
    
    /* get the length of the input string */
    buflen = (mxGetM(prhs[0]) * mxGetN(prhs[0])) + 1;

    /* allocate memory for output string */
    output_buf=(char *)mxCalloc(buflen, sizeof(char));

    /* copy the string data from prhs[0] into a C string input_ buf.    */
    server = mxArrayToString(prhs[0]);
    
    if(server == NULL) 
      mexErrMsgTxt("Could not convert input to string.");
    
    /* call the C subroutine */
    addparamvec_mex(server, buflen, output_buf);

    /* set C-style string output_buf to MATLAB mexFunction output*/
    plhs[0] = mxCreateString(output_buf);
    mxFree(server);
    return;
}

