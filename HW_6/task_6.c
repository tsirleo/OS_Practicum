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

//prll - параллельное (parallel)
//sqntl - последовательное (sequential)

void information(int status)
{
	if (WIFEXITED(status))
		printf("Process exited with status: %d \n", WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		printf("Process terminated with signal №: %d \n", WTERMSIG(status));
	else if (WIFSTOPPED(status))
		printf("Process stopped with stop-signal №: %d \n", WSTOPSIG(status));	    	
}	

int main(int argc, char **argv)
{
	if (argc!=6)
	{
		fprintf(stderr, "Unsufficient number of characters \n");
		exit(1);
	}
	if (!strcmp(argv[argc-1], "prll"))
	{
		pid_t pid1, pid2;
		int status1, status2;		
		if ((pid1=fork())==-1)
		{
			fprintf(stderr, "Error: Failed to calling fork() \n");
			exit(1);	
		}    
		if (pid1==0)
		{
			//сыновний процесс 1
			execl(argv[1], argv[1], argv[2], NULL);
			exit(2);
		}
		if ((pid2=fork())==-1)
		{
			fprintf(stderr, "Error: Failed to calling fork() \n");
			exit(1);
		}
		if (pid2==0)
		{
			//сыновий процесс 2
			execl(argv[3], argv[3], argv[4], NULL);
			exit(2);
		}	 
		//отцовский процесс 
		wait(&status2);
		wait(&status1);
		information(status1);
		information(status2);
	}
    else if (!strcmp(argv[argc-1], "sqntl"))
    {
		pid_t pid;
		int status;
		for(int i=1;i<argc-1;i+=2)
		{
			if ((pid=fork())==-1)
			{
				fprintf(stderr, "Error: Failed to calling fork() \n");
				exit(1);				
			}
			else if (pid==0)
			{ 
				//сыновий процесс
				char *vector_args[3] = {argv[i], argv[i+1], NULL};
				execv(argv[i], vector_args);
				exit(2);
			}
			else
			{
				//отцовский процесс
				wait(&status);
				information(status);
			}
		}
    }
    else
	{
		fprintf(stderr, "The execution parameter is set incorrectly \n");
		exit(1);
	}
    return 0;
}
