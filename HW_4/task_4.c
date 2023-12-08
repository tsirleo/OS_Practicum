#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

void Sort_file(char *file_name)
{
	int fp, length=0, x;
	if ((fp=open(file_name, O_RDWR, 0660))!=-1)
	{
		length=(lseek(fp, 0, SEEK_END)/sizeof(x));
		for (int i=0;i<length;i++)
		{
			lseek(fp, i*sizeof(x), SEEK_SET);
			read(fp, &x, sizeof(x));
			if (x<0)
			{
				lseek(fp, 0, SEEK_END);
				write(fp, &x, sizeof(x));
			}
		}
		for (int i=0;i<length;i++)
		{
			lseek(fp, i*sizeof(x), SEEK_SET);
			read(fp, &x, sizeof(x));
			if (x>=0)
			{
				lseek(fp, 0, SEEK_END);
				write(fp, &x, sizeof(x));
			}
		}
		for(int i=0;i<length;i++)
		{
			lseek(fp, (length+i)*sizeof(x), SEEK_SET);
			read(fp, &x, sizeof(x));
			lseek(fp, i*sizeof(x), SEEK_SET);
			write(fp, &x, sizeof(x));
		}
		ftruncate(fp, length*sizeof(x));
		close(fp);
	}
	else
	{
		fprintf(stderr, "File opening failure \n");
		close(fp);
		exit(1);
    }
}

void Print_result(char *file_name, char *res_file_name)
{
	FILE *fp_res;
	int fp, x;
	if ((fp=open(file_name, O_RDONLY, 0660))!=-1)
	{
		if ((fp_res=fopen(res_file_name, "w"))!=NULL)
		{
			while (read(fp, &x, sizeof(x)))
			{
				fprintf(fp_res, "%d ", x);
			}
			fprintf(fp_res, "%c", '\n');
			fclose(fp_res);
			close(fp);
		}
		else
		{
			fprintf(stderr, "File opening failure \n");
			fclose(fp_res);
			close(fp);
			exit(1);
		}
	}
	else
	{
		fprintf(stderr, "File opening failure \n");
		close(fp);
		exit(1);		
	}
}

int main(int argc, char **argv)
{
	struct stat info1, info2;
	if (argc<3)
	{
		fprintf(stderr, "Unsufficient number of characters \n");
		exit(1);
	}
    stat(argv[1], &info1);
    stat(argv[2], &info2);
    if (info1.st_ino!=info2.st_ino)
    {
		Sort_file(argv[1]);
		Print_result(argv[1], argv[2]);
	}
	else
	{
		fprintf(stderr, "Both names point o the same file \n");
		exit(1);		
	}
	return 0;
}

