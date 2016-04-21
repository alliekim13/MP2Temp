/* Input: frequency file
 * Output: ASCII file
 *
 * createcode.c
 * This program uses an array to build a priority queue
 * Uses linear search to find the smallest element
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000

typedef struct {
    int freq;
    char letter;
    struct Node *left, *right;
} Node;

main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int i;
    char charcount[60];
    char freqline[50];
    char * p;
    char tletter[50];
    char tfreq[50];
    Node * array[MAXSIZE];    
    if (argc != 3) {
	printf("Usage: createcode367 <frequency file> <codebook file>\n");
	return 0;
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");

    fgets(charcount, sizeof charcount, fp1);
    printf("Charcount: %s\n", charcount); 
    i=0;
    while (fgets(freqline, sizeof freqline, fp1)) {
	p = NULL;
	p = strtok(freqline, " \n");
	strcpy(tletter, p);
	printf("Tletter: %s\n", tletter);
	p = strtok(NULL, " \n");
	strcpy(tfreq, p);
	printf("Tfreq: %s\n", tfreq);
    }
    fclose(fp1);
    /*
    while (fgets(freqline, sizeof freqline, fp1) != NULL) {
	    printf("%s", freqline);
	    p=strtok(freqline, "  ");	
	    strcpy(tletter, p);
	    while (p != NULL) {
		printf("%s\n", p);
		p=strtok(NULL, "\n"); 
		strcpy(tfreq, p);
	    }
	    //strcpy(tfreq, p);
	    //printf("Letter: %d\n", atoi(tletter));
	    //printf("Frequency: %d\n", atoi(tfreq));
	    i++;

    }*/

}


