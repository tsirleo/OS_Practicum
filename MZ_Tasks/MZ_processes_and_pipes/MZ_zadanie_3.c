#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>
#include <sys/wait.h>
#define MAXLEN 80

char* Remake_string(char *str, int x)
{
    if (x==1)
        str[(strlen(str))/2]='*';
    else
        for(int i=((strlen(str)/2)-(x/2));i<((strlen(str)/2)+x-1);i++)
            str[i]='*';
    return str;
}

void Open_file_failure(int fd)
{
    if (fd==-1)
    {
        fprintf(stderr, "Error: File opening failure \n");
        close(fd);
        exit(1);
    }
}
int main(int argc, char **argv)
{
    if (argc<2)
    {
        fprintf(stderr, "Error: Unsufficient number of argumets \n");
        exit(1);
    }
    pid_t pid;
    char ch='\n', str[MAXLEN], *file_res_name=argv[1];
    int fd, length, fd_num[2], fd_str[2], fd_len[2], x;
    fd=open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0660);
    Open_file_failure(fd);
    pipe(fd_num);
    pipe(fd_len);
    pipe(fd_str);
    if ((pid=fork())==-1)
    {
        fprintf(stderr, "Error: Failed calling to fork() \n");
        exit(1);
    }
    else if (pid==0)
    {
        //Son process
        close(fd_str[0]);
        close(fd_num[0]);
        close(fd_len[0]);
        printf("Enter a number: ");
        scanf("%d", &x);
        getchar();
        printf("Enter string: ");
        scanf("%s", str);  
        getchar();          
        while (strcmp(str, "exit"))
        {
            length=strlen(str);
            if ((write(fd, str, length*sizeof(ch)))<length)
                perror("write");
            write(fd, &ch, sizeof(ch));
            write(fd_num[1], &x, sizeof(x));
            write(fd_str[1], str, length*sizeof(ch));
            write(fd_len[1], &length, sizeof(length));
            printf("Enter a number: ");
            scanf("%d", &x);
            getchar();
            printf("Enter string: ");
            scanf("%s", str);  
            getchar(); 
        }
        close(fd);
        close(fd_str[1]);
        close(fd_num[1]);
        close(fd_len[1]);
        exit(0);
    }
    else
    {
        //Father process
        close(fd_str[1]);
        close(fd_num[1]);
        close(fd_len[1]);
        while (read(fd_len[0], &length, sizeof(length)))
        {
            read(fd_num[0], &x, sizeof(x));
            read(fd_str[0], str, length*sizeof(ch));
            if ((length)>=x)
            {
                Remake_string(str, x);
                write(fd, str, length*sizeof(ch));
                write(fd, &ch, sizeof(ch));
            }
            else
            {
                ch='*';
                for(int i=0;i<x;i++)
                    write(fd, &ch, sizeof(ch));
                ch='\n';
                write(fd, &ch, sizeof(ch));
            }
        }
        close(fd);
        close(fd_str[0]);
        close(fd_num[0]);
        close(fd_len[0]);
        wait(NULL);
        exit(0);
    }
    return 0;
}

