/*program21.c*/
/*Example of Reading data from a sequential file */
/*fileread.c*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define NROW 60
#define NCOL 40

struct siminfo
{
	int id;
	char name[30];
	int node;
};

typedef struct siminfo SIMINFO;

char *readLine(FILE *file, char *line) {

    if (file == NULL) {
        printf("Error: file pointer is null.");
        exit(1);
    }

    int maximumLineLength = 128;
    char *lineBuffer = (char *)malloc(sizeof(char) * maximumLineLength);

    if (lineBuffer == NULL) {
        printf("Error allocating memory for line buffer.");
        exit(1);
    }

    char ch = getc(file);
    int count = 0;

    while ((ch != '\n') && (ch != EOF)) {
        if (count == maximumLineLength) {
            maximumLineLength += 128;
            lineBuffer = (char *)realloc(lineBuffer, maximumLineLength);
            if (lineBuffer == NULL) {
                printf("Error reallocating space for line buffer.");
                exit(1);
            }
        }
        lineBuffer[count] = ch;
        count++;

        ch = getc(file);
    }

    lineBuffer[count] = '\0';
    /*char line[count + 1];*/
    line=(char *)calloc(count+1,sizeof(char));
    strncpy(line, lineBuffer, (count + 1));
    free(lineBuffer);
    char *constLine = line;
    return constLine;
}



main()
{

	SIMINFO sim;

	FILE *mfptr; /* mfptr = models.dat file pointer*/
 	FILE * fp;
    char * line = NULL;
	char *tokenptr;
    char *tokenseparators = ",";
   
    char patientfilename[] ="data/inflammation-01.csv";
	printf("Simulation log reader.\n");
	
	/*Each file has 60 rows and 40 columns*/
	float patientdata[NROW][NCOL]
	
	
	/*initialize the patient data*/
	for(int row=0; row<NROW; row++)
		for(int col=0; col<NCOL; col++)
			 patientdata[row][col]=0.0;
	
	       fp = fopen(patientfilename, "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

	   
	   /*first count number of numbers in the line*/
       while ((line = readLine(fp, line)) != '\0') {
           printf("Retrieved line of length %s :\n", line);
           printf("%s", line);
       }

	   
	         /*use tokenizer to readline*/
		tokenptr = strtok(line, tokenseparators);
	while(tokenptr != NULL)
	{
		printf("%s\n", tokenptr);
                tokenptr = strtok(NULL, tokenseparators);
	}  
	   
	   
       fclose(fp);
       if (line)
           free((void *)line);
	
	
       
        if((mfptr=fopen("models.dat", "r"))==NULL)
		printf("The file could not be opened!\n");
	else
	{
		printf("%6s %20s %6s\n", "Runid", "Name", "Node");
		fscanf(mfptr, "%d%s%d", &sim.id, sim.name, &sim.node);
		while(!feof(mfptr))
		{
			printf("%6d %20s %6d\n", sim.id, sim.name, sim.node);
			fscanf(mfptr, "%d%s%d", &sim.id, sim.name, &sim.node);
		}

		fclose(mfptr);
	}

	return 0;
}



