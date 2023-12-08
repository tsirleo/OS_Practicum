#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <assert.h>

#define MAXLEN 255

pid_t pid;
int fd;
char ch, str[MAXLEN];

char* Take_word(int fd, char *str)
{
    int i=0;
    if(read(fd, &ch, sizeof(ch)))
    {
        while ((ch==' ')||(ch=='\n'))
            read(fd, &ch, sizeof(ch));
        while ((ch!=' ')&&(ch!='\n'))
        {
            str[i++]=ch;
            read(fd, &ch, sizeof(ch));
        }
        str[i]='\0';
    }
    else
        str[0]='\0';
}

void Son_print_handler(int s)
{
    Take_word(fd, str);
    if (strlen(str)==0)
        kill(getppid(), SIGALRM);
    else
    {
        printf("Son  ");
        printf("%s \n", str);
        kill(getppid(), SIGUSR1);
    }
}

void Father_print_handler(int s)
{
    Take_word(fd, str);
    if (strlen(str)==0)
    {
        kill(pid, SIGKILL);
        exit(0);
    }
    else
    {
        printf("Father  ");
        printf("%s \n", str);
        kill(pid, SIGUSR1);
    }
}

void Son_alarm_handler(int s)
{
    exit(0);
}

void Father_alarm_handler(int s)
{
    kill(pid, SIGKILL);
    wait(NULL);   
    exit(0);  
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
    if (argc!=2)
    {
        fprintf(stderr, "Unsufficient number of arguments \n");
        exit(1);
    }
    fd=open(argv[1], O_RDONLY, 0660);
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
        alarm(3);
        for(;;);
    }
}
