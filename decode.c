#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffmanutil.h"
#include <math.h>

#define HEADER_SIZE 14
#define FIELD_SIZE 8
#define MAX_LINE 10000
typedef struct codeEntry {
	char code[256];
	int codeLength;
} codeEntry;

void buildTree (Node ** nodeptrptr, char input[], int* i, int size)
{ 
	if (*i >= size) return;
	*nodeptrptr = (Node *)malloc(sizeof(Node));
	if (input[*i] == '0') 
		{	//printf("Child\n");							
		(*i) += 1;
		int j;
		int dec = 0;
		for (j=0;j<FIELD_SIZE;j++)
		{
			//printf("%c", input[j+(*i)]);
			if (input[j+(*i)]=='1')
				dec += pow((double)2, (double)(FIELD_SIZE-j-1));
		}
		(*nodeptrptr)->letter = dec;
		(*nodeptrptr)->freq = 0.0;
		//(*nodeptrptr)->right = NULL;
		//(*nodeptrptr)->left = NULL;
		(*i)+=8;
		printf("Building tree\n");
		return;
	}
	(*nodeptrptr)->letter = -1;
	(*nodeptrptr)->freq = 0;
	(*i)+=1;
	//Node * nodeptrptr2 = ((*nodeptrptr)->left);
	buildTree(&((*nodeptrptr)->left), input, i, size);
	buildTree(&((*nodeptrptr)->right), input, i, size);
}

int decode(Node * node, char encoded[], int* i)
{
	if (node == NULL)
		return 0;
	while(node->right != NULL && node->left != NULL)
	{
		if (encoded[*i] == '0')
			node = node->left;
		else node = node->right;
		(*i)+=1;
	}
	return node->letter;
}
int main(int argc, char *argv[]) {
	FILE *fp1, *fp2, *fp3;
	int i = 0;
	//char code[256];
    if (argc != 4) {
		printf("Usage: decode367 <codebook file> <compressed data file> <uncompressed data file>\n");
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
	//printf("File size: %s\n", fileLine);
	for (j=0;j<14;j++)
	{
		printf("%d", fileLine[j]-'0');
		if (fileLine[j]==(1+'0')) 
			filesize += pow((double)2, (double)(14-j-1));
	}
	fgets(fileLine, sizeof(fileLine), fp1);
	printf("File size: %d\n", filesize);
	buildTree(&root, fileLine, &i, filesize);
	char encoded[1000000];
	fgets(encoded, sizeof(encoded), fp2);
	int c;
	char buff;
	i = 0;
	while (encoded[i] != '\0') {
		c = decode(root, encoded, &i);
		fprintf(fp3, "%c", (char)c);
	}
	printf("Reached end\n");
}
