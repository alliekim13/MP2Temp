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
#include "huffmanutil.h"
#define MAXLENGTH 10000
#define MAXBITS 100000
#define HEADER_LENGTH 14
#define NONLEAF 1

void countBits(Node * node, int * bitcount) {
	if (node != NULL) {
		if (node->letter == NONLEAF) {
			*bitcount += 1;
		}
		else *bitcount += 9;
		countBits(node->left, bitcount);
		countBits(node->right, bitcount);
	}
	printf("Bits: %d\n", *bitcount);
}

void writeHeader(FILE *out, Node * node) {
	int *bitcount;
	*bitcount = 0;
	countBits(node, bitcount);
	*bitcount += HEADER_LENGTH;
	int bits;
	int i = 0;
	for(i = 13; i >= 0; i--){
		if((*bitcount & (1 << i)) != 0){
			bits = 1;
     	}else{
			bits = 0;
		}
		fprintf(out, "%d", bits);
	}
	fprintf(out, "\n");
}

void writeEncoded(int c, FILE* out)
{	printf("encoding: %d\n", c);
	int bits;
	if (c == 1) {
		bits = 1;
	fprintf(out, "%d", bits);
	}
	else {
		fprintf(out, "0");
		int i = 0;
		for(i = 7; i >= 0; i--){
			if((c & (1 << i)) != 0){
				bits = 1;
	     	}else{
				bits = 0;
			}
			fprintf(out, "%d", bits);
		}
	}
}

void encode(Node *node, FILE* out)
{
	printf("encoding\n");
	if (node!=NULL) {
		writeEncoded(node->letter, out);
		encode(node->left, out);
		encode(node->right, out);
	}
}

int CmpTrees(const void *x, const void *y)
{
	const Node **a = (const Node **) x;
	const Node **b = (const Node **) y;
	if ((*a)->freq == (*b)->freq) return 0;
	else if ((*a)->freq < (*b)->freq) return 1;
	else return -1;
}

/*void VLRTraverseTree(Node *node)
{
	if (node != NULL) {
		//dec2bin(node->letter);
		VLRTraverseTree(node->left);
		VLRTraverseTree(node->right);
	}
}*/

Node * buildTree(Node* array[], int size) 
{
	printf("BuildTree\n");
	int i = 0;
	while (size > 1)
	{
		Node *add = (Node *)malloc(sizeof(Node));
		for (i = 0; i < size; i++)
		{
			printf("%d\n", array[i]->letter);
		}
		qsort(array, size, sizeof(Node *), CmpTrees);
		for (i = 0; i < size; i++)
		{
			printf("%d\n", array[i]->letter);
		}
		size -= 1;
		add -> left = array[size];
		size -=1;
		add -> right = array[size];
		add->freq = add->right->freq + add->left->freq;
		add->letter = 1;
		//printf("Freq: %f\n", add->freq);
		array[size++] = add;
	}
	return array[0];
}


int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    int i;
    char charcount[60];
    char freqline[50];
    char * p;
    char tletter[50];
    char tfreq[50];
    Node * array[MAXSIZE];   
	char * bitstream[MAXBITS];
    if (argc != 3) {
	printf("Usage: createcode367 <frequency file> <codebook file>\n");
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
	fclose(fp1);
	fclose(fp2);
}



