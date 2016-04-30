#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "huffmanutil.h"
#define HEADER_SIZE 14
#define FIELD_SIZE 8
#define MAX_LINE 10000
typedef struct codeEntry {
	int ;
	char code[256];
} codeEntry;

void buildTree (Node ** nodeptrptr, char input[], int* i, int size)
{ 
	if (*i >= size) return;
	*nodeptrptr = (Node *)malloc(sizeof(Node));
	if (input[*i] == '0') 
	{								
		(*i) += 1;
		int j;
		int dec = 0;
		for (j=0;j<FIELD_SIZE-1;j++)
		{
			if (input[j]=='0'+1)
				dec += pow((double)2, (double)(FIELD_SIZE-1-j));
		}
		(*nodeptrptr)->letter = dec;
		(*nodeptrptr)->freq = 0.0;
		(*i)+=8;
	}
	(*nodeptrptr)->letter = -1;
	(*nodeptrptr)->freq = 0;
	(*i)+=1;
	Node * nodeptrptr2 = ((*nodeptrptr)->left);
	buildTree(&((*nodeptrptr)->left), input, i, size);
	buildTree(&((*nodeptrptr)->right), input, i, size);
}

codeEntry encodeEntry(Node * node, int key)
{
	if (node == NULL) {
		return -1;
	}
	
}
int main(int argc, char *argv[])
{
    FILE *fp1, *fp2, *fp3;
    int i = 0;
    char charcount[60];
    char freqline[50];
    char * p;
    Node * array[MAXSIZE];
    if (argc != 4) {
		printf("Usage: createcode367 <codebook file> <data file> <compressed data file>\n");
		return 0;
    }
	
    fp1 = fopen(argv[1], "r"); // codebook file
    fp2 = fopen(argv[2], "r");
	fp3 = fopen(argv[3], "w");
	Node * root = NULL;
	char fileLine[MAX_LINE];
	fgets(fileLine, sizeof(fileLine), fp1);
	int j;
	int filesize = 0;
	printf("File size: %s\n", fileLine);
	for (j=0;j<14;j++)
	{
		if (fileLine[j]==(1+'0')) 
			filesize += pow((double)2, (double)(13-j));
	}
	fgets(fileLine, sizeof(fileLine), fp1);
	printf("File size: %d\n", filesize);
	buildTree(&root, fileLine, &i, filesize);
	codeEntry codebook[256];
	for (j = 0; j<256; j++) 
	{
		codebook[j] = encodeEntry(root, j);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

//If not a leaf (if in == 1)
	//Next number is the left child
	//Following number is the right child