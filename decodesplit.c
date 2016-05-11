#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAXSIZE 1000000
int main(int argc, char *argv[]) {
	int i;
	int c;
	int sum = 0;
	//char codefile[MAXSIZE];
	FILE *compressed, *codebook, *encoded;
	if (argc != 4) {
		printf("Usage: <compressed data file> <codebook file> <encoded data file>\n");
	}

	compressed = fopen(argv[1], "r");
	codebook = fopen(argv[2], "w");
	encoded = fopen(argv[3], "w");
	//printf("Filesize:");
	for (i = 0; i < 14; i++)
	{	
		c = fgetc(compressed);
		//printf("%d", c - '0');
		fprintf(codebook, "%d", c-'0');
		if (c == '1') {
			sum += pow((double)2, (double)(14-i-1));
		}
	}
	fprintf(codebook, "\n");
	//printf("File size decode split: %d\n", sum);
	//printf("Hi2\n");
	//fgets(codefile, sizeof(codefile), compressed);
	//printf("Codefile:%s\n", &codefile);
	i = 0;
	while ((c = fgetc(compressed)) != EOF) {	
		if (c != EOF) {
			if (i >= 1 && i < sum-14 + 1) {
				fprintf(codebook, "%d", c-'0');
				//printf("%d", c-'0');
			}
			else if (i >= sum - 14 + 1) {
				fprintf(encoded, "%d", c-'0');
			}
		}
		i++;
	}
	fclose(compressed);
	fclose(codebook);
	fclose(encoded);	
}
