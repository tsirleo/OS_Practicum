#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *fp;
	int x;
	if (argc<2)
	{
		fprintf(stderr, "Unsufficient number of characters \n");
		exit(1);
	}
	fp=fopen(argv[1], "r");
	while (fread(&x, sizeof(x), 1, fp))
	{
		printf("%d  ", x);
	}
	printf("\n");
	fclose;
	return 0;
}


