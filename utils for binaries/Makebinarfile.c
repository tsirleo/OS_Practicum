#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int N,x;
	if (argc<2)
	{
		fprintf(stderr, "Unsufficient number of characters \n");
		exit(1);
	}
	printf("Enter the number of file elements: ");
	scanf("%d", &N);
	getchar();
	FILE *fp;
	fp=fopen(argv[1], "w");
	for(int i=0; i<N; i++)
	{
		scanf("%d", &x);
		fwrite(&x, sizeof(x), 1, fp);
	}
	fclose;
	return 0;
}

