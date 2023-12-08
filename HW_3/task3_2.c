#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void Delete_string (char* file_name, int n) 
{
    FILE *fp, *fp_copy;
    char *str;
    char ch;
    fp=fopen(file_name, "r");
    if (fp==NULL)
    {
        fprintf(stderr, "File opening failure \n");
        exit(1);
    }
	fp_copy=fopen("Help_del_copy.txt", "w");
    if (fp_copy==NULL)
    {
        fprintf(stderr, "File opening failure \n");
        exit(1);
    }
    while ((ch=fgetc(fp))!=EOF)
    {
		unsigned basis=4;
		unsigned size=0;
		unsigned i=0;
		str=(char*)malloc(size+=basis);
		str[i++]=ch;
		while (((ch=fgetc(fp))!='\n')&&(ch!=EOF))
		{
			str[i++]=ch;
			if (i==size)
				str= (char*)realloc(str, size+=basis);
		}
		str[i]='\0';
        if (strlen(str)>=n)
        {
			fputs(str, fp_copy);
			fputc('\n', fp_copy);
        }
		free(str);
	}
    fclose(fp);
	fclose(fp_copy);
    remove(file_name);
    rename("Help_del_copy.txt", file_name);
}

int main(int argc, char **argv)
{
	if (argc<3)
    {
        fprintf(stderr, "Unsufficient number of arguments \n");
        exit(1);
    }
    Delete_string(argv[1], atoi(argv[2]));
	return 0;
}
