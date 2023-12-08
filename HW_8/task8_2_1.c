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
	printf("\nHandler received a signal Ctrl+C \n");	
}

int main()
{
	signal(SIGINT, Signal_handler);
	while(1)
	{	
	    pause();
        printf("Signal processing wasn't reset to default value \n");	    
	}  	
	return 0;
}

