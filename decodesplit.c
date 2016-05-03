#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 1000000
int main(int argc, char *argv[]) {
	int i, j;
	int c;
	int sum = 0;
	char codefile[MAXSIZE];
	FILE *compressed, *codebook, *encoded;
	if (argc != 4) {
		printf("Usage: <compressed data file> <codebook file> <encoded data file>\n");
	}

	compressed = fopen(argv[1], "r");
	codebook = fopen(argv[2], "w");
	encoded = fopen(argv[3], "w");
	printf("Hi\n");
	for (i = 0; i < 14; i++)
	{	
		c = fgetc(compressed);
		if (c == '1') {
			sum += pow((double)2, (double)(14-i-1));
		}
	}
	printf("Hi2\n");
	fgets(codefile, sizeof(codefile), compressed);
	i = 0;
	while ((c = fgetc(compressed)) != EOF) {	
		if (c != EOF) {
			if (i >= 14 && i < sum) {
				fprintf(codebook, "%d", c-'0');
			}
			else if (i >= sum) {
				fprintf(encoded, "%d", c-'0');
			}
		}
		i++;
	}	
}
