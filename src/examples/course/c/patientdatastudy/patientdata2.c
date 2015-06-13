/*program21.c*/
/*Example of Reading data from a sequential file */
/*fileread.c*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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
   
	printf("Simulation log reader.\n");
	
	
	       fp = fopen("/etc/motd", "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

       while ((line = readLine(fp, line)) != '\0') {
           printf("Retrieved line of length %zu :\n", read);
           printf("%s", line);
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



