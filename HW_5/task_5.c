#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char **argv)
{
	FILE *fp;
	char *file_name, *cur_st, *prev_st;
	int flag_c=0, flag_d=0, flag_u=0, flag_s=0, number=0, count=0;
	char ch;
    if (argc<2)
    {
        fprintf(stderr, "Error: Unsufficient number of arguments \n");
        exit(2);
    }
	for(int i=1;i<argc;i++)
	{
		if (!strcmp(argv[i], "-c"))
			flag_c=1;
		else if (!strcmp(argv[i], "-u"))
			flag_u=1;
		else if (!strcmp(argv[i], "-d"))
			flag_d=1;
		else if (!strcmp(argv[i], "-s"))
		{
			flag_s=1;
			i+=1;
			for(int j=0; j<strlen(argv[i]);j++)
			{
				if (!isdigit(argv[i][j]))
				{
					fprintf(stderr, "Error: Invalid number of bytes to skip \n");
					exit(2);					
				}
			}
			number=atoi(argv[i]);
		}
		else 
		{
			file_name=(char*)malloc(strlen(argv[i])+1);
			strcpy(file_name, argv[i]);
		}
	}
	if ((flag_u)&&(flag_d))
		return 0;
	if ((fp=fopen(file_name, "r"))!=NULL)
	{
		unsigned basis=4;
		unsigned size=0;
		unsigned i=0;
		cur_st=(char*)malloc(size+=basis);
		while (((ch=fgetc(fp))!='\n')&&(ch!=EOF))
		{
			cur_st[i++]=ch;
			if (i==size)
				cur_st= (char*)realloc(cur_st, size+=basis);
		}
		cur_st[i]='\0';	
		prev_st=(char*)malloc(strlen(cur_st)+1);
		strcpy(prev_st, cur_st);
		free(cur_st);
		count+=1;
		while ((ch=fgetc(fp))!=EOF)
		{
			unsigned basis=4;
			unsigned size=0;
			unsigned i=0;
			cur_st=(char*)malloc(size+=basis);
			cur_st[i++]=ch;
			while (((ch=fgetc(fp))!='\n')&&(ch!=EOF))
			{
				cur_st[i++]=ch;
				if (i==size)
					cur_st= (char*)realloc(cur_st, size+=basis);
			}
			cur_st[i]='\0';	
			if ((strcmp(cur_st+number, prev_st+number))||(strlen(cur_st+number)!=strlen(prev_st+number)))
			{
				if (flag_u)
				{ 
					if (count==1)
					{
						if (flag_c)
							fprintf(stdout, "	%d %s \n", count, prev_st);
						else
							fprintf(stdout, "%s \n", prev_st);
					}
				}
				else if (flag_d)
				{
					if (count>1)
					{
						if (flag_c)
							fprintf(stdout, "	%d %s \n", count, prev_st);
						else
							fprintf(stdout, "%s \n", prev_st);
					}
				}
				else
				{
					if (flag_c)
						fprintf(stdout, "	%d %s \n", count, prev_st);
					else
						fprintf(stdout, "%s \n", prev_st);
				}
				count=1;
				free(prev_st);
				prev_st=(char*)malloc(strlen(cur_st)+1);
				strcpy(prev_st, cur_st);
				free(cur_st);				
			}
			else
			{
				free(cur_st);
				count+=1;
			}
		}
		if (flag_u)
		{ 
			if (count==1)
			{
				if (flag_c)
					fprintf(stdout, "	%d %s \n", count, prev_st);
				else
					fprintf(stdout, "%s \n", prev_st);
			}
		}
		else if (flag_d)
		{
			if (count>1)
			{
				if (flag_c)
					fprintf(stdout, "	%d %s \n", count, prev_st);
				else
					fprintf(stdout, "%s \n", prev_st);
			}
		}
		else
		{
			if (flag_c)
				fprintf(stdout, "	%d %s \n", count, prev_st);
			else
				fprintf(stdout, "%s \n", prev_st);
		}
		free(prev_st);
	}
	else
	{
		fprintf(stderr, "Error: File opening failure or file doesn't exist \n");
		fclose(fp);
		exit(1);		
	}
	fclose(fp);
	free(file_name);
	return 0;
}

