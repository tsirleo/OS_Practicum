#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <assert.h>

void Pipe_call_error(int p)
{
	if (p==-1)
	{
		fprintf(stderr, "Error: Failed to calling pipe() \n");
		exit(1);				
	}	
}

void Fork_call_error(pid_t pid)
{
	if (pid==-1)
	{
		fprintf(stderr, "Error: Failed to calling fork() \n");
		exit(1);				
	}
}

int main(int argc, char **argv)
{
	pid_t pid1, pid2;
	int p, num, MAXNUM, fd1[2], fd2[2], fd3[3];
	if (argc!=3)
	{
		fprintf(stderr, "Unsufficient number of arguments \n");
		exit(1);
	}
	num=atoi(argv[1]);
	MAXNUM=atoi(argv[2]);
	p=pipe(fd1); //Father->son pipe
	Pipe_call_error(p);
	p=pipe(fd3); //Grandson->father pipe
	Pipe_call_error(p);
	pid1=fork();
	Fork_call_error(pid1);
	if (pid1==0)
	{
		//Son process
		p=pipe(fd2); //Son->grandson pipe
		Pipe_call_error(p);
		pid2=fork();
		Fork_call_error(pid2);
		if (pid2==0)
		{
			//Grandson process
			close(fd1[0]);
			close(fd1[1]);
			close(fd2[1]);
			close(fd3[0]);
			while (read(fd2[0], &num, sizeof(num)))
			{
				if (num>MAXNUM)
				{
					close(fd2[0]);
					close(fd3[1]);
					exit(0);
				}	
				else
				{
					printf("Number=%d  PID=%d\n", num, getpid());
					num+=1;
					write(fd3[1], &num, sizeof(num));	
				}
			}			
		}
		else
		{
			//Son process
			close(fd1[1]);
			close(fd2[0]);
			close(fd3[0]);
			close(fd3[1]);
			while (read(fd1[0], &num, sizeof(num)))
			{
				if (num>MAXNUM)
				{
					close(fd1[0]);
					close(fd2[1]);
					exit(0);
				}	
				else
				{
					printf("Number=%d  PID=%d\n", num, getpid());
					num+=1;
					write(fd2[1], &num, sizeof(num));	
				}
			}	
		}
	}
	else
	{
		//Father process
		close(fd1[0]);
		close(fd3[1]);
		printf("Number=%d  PID=%d\n", num, getpid());
		num+=1;
		write(fd1[1], &num, sizeof(num));
		if (num>=MAXNUM)
		{
			close(fd1[1]);
			close(fd3[0]);
			for(int i=0;i<2;i++)
				wait(NULL);
			exit(0);
		}	
		while (read(fd3[0], &num, sizeof(num)))
		{
			if (num>MAXNUM)
			{
				close(fd1[1]);
				close(fd3[0]);
				for(int i=0;i<2;i++)
					wait(NULL);
				exit(0);
			}	
			else
			{
				printf("Number=%d  PID=%d\n", num, getpid());
				num+=1;
				write(fd1[1], &num, sizeof(num));
			}				
		}
	}
	return 0;
}

