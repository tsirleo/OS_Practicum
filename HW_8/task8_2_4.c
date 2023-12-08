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

void Signal_handler(int s)
{
	printf("Function 'wait' was reset \n");
}

int main()
{
	pid_t pid;
	if ((pid=fork())==-1)
	{
		fprintf(stderr, "Error: Failed to calling pipe() \n");
		exit(1);	
	}
	else if (pid==0)
	{
		//Son process
		kill(getppid(), SIGINT);
		sleep(5);
		exit(0);
	}
	else
	{
		//Father process
		signal(SIGINT, Signal_handler);
		wait(NULL);
		printf("Function 'wait' was finished \n");
		exit(0);
	}
	return 0;
}

