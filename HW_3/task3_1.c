#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Open_file_error(FILE *fp)
{
    if (fp==NULL)
    {
        fprintf(stderr, "File opening failure \n");
        exit(1);
    }
    return;
}

int File_length(char *file_name) 
{
	FILE* fp;
	int length=0;
	char ch;
	fp = fopen(file_name, "r");
	Open_file_error(fp);
	while((ch=fgetc(fp))!=EOF) 
	{
		length+=1;
	}
	fclose(fp);
	return length;
}

void Combine_two_files_into_third(char *file_name1, char *file_name2, char *file_res_name, int n)
{
	FILE *f1, *f2, *f_res, *f_help1, *f_help2;
	char ch;
	char *str;
	f1 = fopen(file_name1, "r");
	Open_file_error(f1);
	while ((ch=fgetc(f1))!=EOF)
    {
		unsigned basis=4;
		unsigned size=0;
		unsigned i=0;
		str=(char*)malloc(size+=basis);
		str[i++]=ch;
		while (((ch=fgetc(f1))!='\n')&&(ch!=EOF))
		{
			str[i++]=ch;
			if (i==size)
				str= (char*)realloc(str, size+=basis);
		}
		str[i]='\0';
            f_help1=fopen("Help1.txt", "a");
			Open_file_error(f_help1);
			fputs(str, f_help1);
			fclose(f_help1);
		free(str);
	}
	fclose(f1);
	f2 = fopen(file_name2, "r");
	Open_file_error(f2);
	while ((ch=fgetc(f2))!=EOF)
    {
		unsigned basis=4;
		unsigned size=0;
		unsigned i=0;
		str=(char*)malloc(size+=basis);
		str[i++]=ch;
		while (((ch=fgetc(f2))!='\n')&&(ch!=EOF))
		{
			str[i++]=ch;
			if (i==size)
				str= (char*)realloc(str, size+=basis);
		}
		str[i]='\0';
            f_help2=fopen("Help2.txt", "a");
			Open_file_error(f_help2);
			fputs(str, f_help2);
			fclose(f_help2);
		free(str);
	}	
	fclose(f2);
	f1 = fopen("Help1.txt", "r");
	Open_file_error(f1);
	f2 = fopen("Help2.txt", "r");
	Open_file_error(f2);
	f_res = fopen(file_res_name, "w");
	Open_file_error(f_res);
	str=(char*)malloc(n+1);
	if (File_length("Help1.txt")>File_length("Help2.txt"))
	{
		while (fgets(str, n+1, f2))
		{
			fputs(str, f_res);
			fputc('\n', f_res); 
			fgets(str, n+1, f1);
			fputs(str, f_res);
			fputc('\n', f_res);
		}
		while (fgets(str, n+1, f1))
		{
			fputs(str, f_res);
			fputc('\n', f_res);			
		}
	}
	else if (File_length(file_name1)<File_length(file_name2))
	{
		while (fgets(str, n+1, f1))
		{
			fputs(str, f_res);
			fputc('\n', f_res); 
			fgets(str, n+1, f2);
			fputs(str, f_res);
			fputc('\n', f_res);
		}
		while (fgets(str, n+1, f2))
		{
			fputs(str, f_res);
			fputc('\n', f_res);			
		}
	}
	else if (File_length(file_name1)==File_length(file_name2))
	{
		while ((!feof(f2))||(feof(f1)))
		{
			fgets(str, n+1, f1);
			fputs(str, f_res);
			fputc('\n', f_res); 
			fgets(str, n+1, f2);
			fputs(str, f_res);
			fputc('\n', f_res);
		}
	}
	free(str);
	fclose(f_res);
	fclose(f1);
	remove("Help1.txt");
	fclose(f2);
	remove("Help2.txt");
}

int main(int argc, char **argv)
{
	if (argc<5)
    {
        fprintf(stderr, "Unsufficient number of arguments \n");
        exit(1);
    }	
    Combine_two_files_into_third(argv[1], argv[2], argv[3], atoi(argv[4]));
	return 0;
}

