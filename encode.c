#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "huffmanutil.h"
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
		{	printf("Child\n");							
		(*i) += 1;
		int j;
		int dec = 0;
		for (j=0;j<FIELD_SIZE;j++)
		{
			printf("%c", input[j+(*i)]);
			if (input[j+(*i)]=='1')
				dec += pow((double)2, (double)(FIELD_SIZE-j-1));
		}
		(*nodeptrptr)->letter = dec;
		(*nodeptrptr)->freq = 0.0;
		(*nodeptrptr)->right = NULL;
		(*nodeptrptr)->left = NULL;
		(*i)+=8;
		return;
	}
	(*nodeptrptr)->letter = -1;
	(*nodeptrptr)->freq = 0;
	(*i)+=1;
	Node * nodeptrptr2 = ((*nodeptrptr)->left);
	buildTree(&((*nodeptrptr)->left), input, i, size);
	buildTree(&((*nodeptrptr)->right), input, i, size);
}

void encodeEntry(Node * node, codeEntry entries[], char code[], int size)
{
	if (node == NULL) {
		return;
	}
	//printf("Data: %i\n", node->letter);
		printf("Hi\n");
	if (node->left == NULL && node->right == NULL)
	{
		int i;
		printf("Hi2\n");
		for (i=0;i<size;i++) 
			{	printf("Break1\n");
			if (node->letter != -1)
				entries[node->letter].code[i]=code[i]; 
		}
		return;
	}
	code[size] = '0';
				printf("Break2\n");
	encodeEntry(node->left, entries, code, size + 1);
	code[size] = '1';
	encodeEntry(node->right, entries, code, size + 1);
}

void VLRTraverseTree(Node * root) {
if (root!= NULL) {
	printf("Lett: %d\n", root->letter);
	VLRTraverseTree(root->left);
	VLRTraverseTree(root->right);
}
}

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2, *fp3;
    int i = 0;
    char charcount[60];
    char freqline[50];
    char * p;
	char code[256];
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
	VLRTraverseTree(root);
	codeEntry codebook[256];
	for (j = 0; j < 256; ++j) {
		codebook[j].codeLength = 0;
	}
	encodeEntry(root, codebook, code, 0);
	for (j=0;j<256;j++)
		printf("%d = %s\n", j, codebook[j].code);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
}

//If not a leaf (if in == 1)
	//Next number is the left child
	//Following number is the right child