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
#include <signal.h>

int num, MAXNUM, fd[2];
pid_t target_pid, father_pid, last_pid;

void Signal_handler(int s)
{
	read(fd[0], &num, sizeof(num));
	read(fd[0], &last_pid, sizeof(last_pid));
	if (num<=MAXNUM)
	{
		printf("Number=%d  PID=%d\n", num, getpid());
		num+=1;
		write(fd[1], &num, sizeof(num));
		write(fd[1], &last_pid, sizeof(last_pid));
		kill(target_pid, SIGUSR1);
	}	
	else if (target_pid==father_pid)
	{
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else
	{
		kill(last_pid, SIGKILL);
	}
}

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
	int p, N;
	if (argc!=4)
	{
		fprintf(stderr, "Unsufficient number of arguments \n");
		exit(1);
	}
	num=atoi(argv[1]);
	MAXNUM=atoi(argv[2]);
	N=atoi(argv[3]);
	if (N<2)
	{
		fprintf(stderr, "The number of processes is set incorrectly \n");
		exit(1);
	}	
	signal(SIGUSR1, Signal_handler);
	p=pipe(fd);
	Pipe_call_error(p);
	write(fd[1], &num, sizeof(num));
	printf("Rut PID = %d\n", getpid());
	father_pid=getpid();
	for(int i=1;i<=N-1;i++)
	{
		target_pid=fork();
		Fork_call_error(target_pid);
		if (target_pid==0)
		{
			if (i==N-1)
			{
				target_pid=father_pid;
				last_pid=getpid();
				write(fd[1], &last_pid, sizeof(last_pid));
				kill(target_pid, SIGUSR1);
				for(;;);
			}
		}
		else
		{
			wait(NULL);
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
	}
	return 0;
}
