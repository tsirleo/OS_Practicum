#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>

pid_t pid;

void Son_print_handler(int s)
{
    printf("Son \n");
    kill(getppid(), SIGUSR1);
}

void Father_print_handler(int s)
{
    printf("Father \n");
    kill(pid, SIGUSR1);
}

void Son_alarm_handler(int s)
{
    exit(0);
}

void Father_alarm_handler(int s)
{
    signal(SIGINT, SIG_DFL);    
    kill(pid, SIGKILL);
    printf("\n");
    while (1)
    {
        printf("Father \n");
        sleep(1);
    }   
}

void Fork_calling_error(pid_t pid)
{
    if (pid==-1)
    {
        fprintf(stderr, "Error: Failed calling to fork() \n");
        exit(1);
    }
}

int main(int argc, char **argv)
{
    pid=fork();
    Fork_calling_error(pid);
    if (pid==0)
    {
        //Son process
        signal(SIGALRM, Son_alarm_handler);
        signal(SIGUSR1, Son_print_handler);
        alarm(3);
        kill(getppid(), SIGUSR1);
        for(;;);
    }
    else
    {
        //Father process
        signal(SIGALRM, Father_alarm_handler);
        signal(SIGUSR1, Father_print_handler);
        signal(SIGINT, SIG_DFL);
        alarm(3);
        for(;;);
    }
}

