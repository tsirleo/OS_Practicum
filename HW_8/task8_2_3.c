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
	printf("Signal send to process with PID = %d \n", getpid());
}

int main()
{
	signal(SIGINT, Signal_handler);	
	printf("Rut PID = %d \n", getpid()); 	
	if (!fork());
	else
		kill(0, SIGINT);
	return 0;
}

