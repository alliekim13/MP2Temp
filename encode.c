#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffmanutil.h"

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2, *fp3;
    int i;
    char charcount[60];
    char freqline[50];
    char * p;
    char tletter[50];
    char tfreq[50];
    Node * array[MAXSIZE];   
	char * bitstream[MAXBITS];
    if (argc != 3) {
	printf("Usage: createcode367 <codebook file> <data file> <compressed data file>\n");
    }

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "w");

    fgets(charcount, sizeof charcount, fp1);
    printf("Charcount: %s\n", charcount); 
    i=0;
    int size = 0;
    // Add frequencies to queue
    while (fgets(freqline, sizeof freqline, fp1)) {
		p = NULL;
		p = strtok(freqline, " \n");
		strcpy(tletter, p);
		p = strtok(NULL, " \n");
		strcpy(tfreq, p);
		Node * toadd = (Node *)calloc(1, sizeof(Node));
		printf("%d\n", atoi(tletter));
		printf("%f\n", atof(tfreq));
		toadd -> letter = atoi(tletter);
		toadd -> freq = atof(tfreq);
		toadd -> right = NULL;
		toadd -> left = NULL;
		array[size++] = toadd;
	}
	Node *node = buildTree(array, size);
	writeHeader(fp2, node);
	encode(node, fp2);
	fclose(fp2);
}