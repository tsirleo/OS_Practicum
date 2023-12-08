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
pid_t target_pid, father_pid;

void Signal_handler(int s)
{
	read(fd[0], &num, sizeof(num));
	if (num<=MAXNUM)
	{
		printf("Number=%d  PID=%d\n", num, getpid());
		num+=1;
		write(fd[1], &num, sizeof(num));
		kill(target_pid, SIGUSR1);
	}	
	else if (target_pid==father_pid)
	{
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	else
		kill(target_pid, SIGUSR1);
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
	int p;
	if (argc!=3)
	{
		fprintf(stderr, "Unsufficient number of arguments \n");
		exit(1);
	}
	num=atoi(argv[1]);
	MAXNUM=atoi(argv[2]);
	signal(SIGUSR1, Signal_handler);
	p=pipe(fd);
	Pipe_call_error(p);
	printf("Rut PID = %d\n", getpid());
	father_pid=getpid();
	target_pid=fork();
	Fork_call_error(target_pid);
	if (target_pid==0)
	{
		//Son process
		target_pid=fork();
		Fork_call_error(target_pid);
		if (target_pid==0)
		{
			//Grandson process
			target_pid=father_pid;
			kill(target_pid, SIGUSR1);
			for(;;);
		}
		else
		{
			//Son process
			wait(NULL);
			close(fd[0]);
			close(fd[1]);
			exit(0);
		}
	}
	else
	{
		//Father process
		write(fd[1], &num, sizeof(num));
		wait(NULL);
		close(fd[0]);
		close(fd[1]);
		exit(0);
	}
	return 0;
}

