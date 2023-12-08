#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <limits.h>
#include <sys/wait.h>


int main(int argc, char **argv)
{
	for(int i=0; i<10;i++)
		printf("PID = %d \nArgument = %s \n", getpid(), argv[1]);
    return 0;
}
