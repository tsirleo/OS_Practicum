#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>

int **fd, flag_out=0;
char *file_out;

void Open_pipes(int n_coms)
{	
	int p;
	for(int i=0;i<n_coms-1;i++)
	{
		p=pipe(fd[i]);
		if (p==-1)
		{
			perror("Pipe opening error");
		}
	}
}

void Close_pipes(int n_coms)
{
	for(int i=0;i<n_coms-1;i++)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}	
}

int main(int argc, char **argv)
{
	char *str, ch, ***args;
	int *n_arg, n_com=1, fd_out;
	pid_t pid;
	
	for(int i=0;i<argc;i++)
	{
		if (!strcmp(argv[i],"+"))
			n_com+=1;
	}
	for(int i=0;i<n_com-1;i++)
		fd[i]=(int *)malloc(2*sizeof(int));
	if (!strcmp(argv[argc-2], "-o"))
	{
		flag_out=1;
		file_out=argv[argc-1];
	}
	n_arg=(int*)malloc(n_com*sizeof(int));
	int j=0;
	for(int i=0;i<argc;i++)
	{
		if(flag_out&&(i==argc-2))
		{
			n_arg[j]+=1;
			break;
		}
		else if(!strcmp(argv[i],"+"))
		{
			n_arg[j]+=1;
			j+=1;
		}
		else
			n_arg[j]+=1;
	}
	args=(char ***)malloc((n_com)*sizeof(char **));	
	for(int i=0;i<n_com;i++)
		args[i]=(char **)malloc((n_arg[i])*sizeof(char *));
	
	j=0;
	int k=0;
	for(int i=0; i<argc;i++)
	{
		if (!strcmp(argv[i],"-o"))
		{
			args[j][k]=NULL;
			break;
		}
		else if(!strcmp(argv[i],"+"))
		{
			args[j][k]=NULL;
			j+=1;
			k=0;
		}	
		else 
		{
			args[j][k]=argv[i];
			k+=1;
		}	
	}
	
	Open_pipes(n_com);
	for(int i=0;i<n_com;i++)
	{
		pid=fork();
		if (pid==-1)
		{
			perror("fork error");
			exit(1);
		}
		if (pid==0)
		{
			if (i==0)
			{
				if (n_com==1)
				{
					if (flag_out)
					{
						fd_out=open(file_out, O_APPEND|O_CREAT|O_WRONLY, 0660);
						if (fd_out==-1)
						{
							perror("file opening error");
							exit(1);
						}
						dup2(fd_out, 1);
						close(fd_out);
					}
						execvp(args[i][0], args[i]);
						perror("exec error");
						exit(1);
				}
				dup2(fd[i][1], 1);
				Close_pipes(n_com);
				execvp(args[i][0], args[i]);
				perror("exec error");
				exit(1);
			}
			else if ((i>0)&&(i<(n_com-1)))
			{
				dup2(fd[i-1][0], 0);
				dup2(fd[i][1], 1);
				Close_pipes(n_com);
				execvp(args[i][0], args[i]);
				perror("exec error");
				exit(1);
			}
			else if (i==(n_com-1))
			{
				if (flag_out)
				{
					fd_out=open(file_out, O_APPEND|O_CREAT|O_WRONLY, 0660);
					if (fd_out==-1)
					{
						perror("file opening error");
						exit(1);
					}
					dup2(fd_out, 1);
					close(fd_out);
				}
				dup2(fd[i-1][0], 0);
				Close_pipes(n_com);
				execvp(args[i][0], args[i]);
				perror("exec error");
				exit(1);				
			}
		}
	}
	Close_pipes(n_com);
	for(int i=0; i<n_com;i++)
		wait(NULL);
	return 0;
}














