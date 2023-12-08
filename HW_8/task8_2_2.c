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

void Signal_int_handler(int s)
{
	printf("\nHandler received a signal Ctrl+C \n");	
}

void Signal_stop_handler(int s)
{
	printf("\nHandler received a signal Ctrl+Z \n");	
}

void Signal_handler_a(int s)
{
	alarm(10);
    printf("\nHandler received a signal Ctrl+Z \n");
    signal(SIGTSTP, Signal_stop_handler);
    pause();	
}

void Signal_handler_b(int s)
{
	alarm(10);
    printf("\nHandler received a signal Ctrl+Z \n");
    signal(SIGINT, Signal_int_handler);
    pause(); 	
}

int main(int argc, char **argv)
{
	if (argc!=2)
	{
		fprintf(stderr, "Unsufficient number of arguments \n");
		exit(1);
	}	
	if (!strcmp(argv[1],"a"))
	{
		signal(SIGTSTP, Signal_handler_a);
		while(1)	
			pause();    	
	}
	else if (!strcmp(argv[1],"b"))
	{
        signal(SIGTSTP, Signal_handler_b);
		while(1)
			pause();		
	}
}



