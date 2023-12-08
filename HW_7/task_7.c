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

char* Read_string(int fd)
{
	unsigned basis=4;
	unsigned size=0;
	unsigned i=0;
	char ch;
	char *str=(char*)malloc(size+=basis);
	while ((read(fd, &ch, sizeof(ch)))&&(ch!='\n'))
	{
		str[i++]=ch;
		if (i==size)
			str=(char*)realloc(str, size+=basis);
	}
	str[i]='\0';
	if (!strcmp(str, "\0"))
	{
		str=(char*)realloc(str, 2*sizeof(ch));
		strcpy(str, "\n");
		return str;		
	}
	else
	{
		str=(char*)realloc(str, i*sizeof(ch));
		return str;
	}
}

void Open_file_error(int fd)
{
    if (fd==-1)
    {
        fprintf(stderr, "File opening failure \n");
        close(fd);
        exit(1);
    }
    return;
}

int Number_of_strings_in_file(char *file_name)
{
	int fd, number = 0;
    char ch;
	fd=open(file_name, O_RDONLY, 0660);
	Open_file_error(fd);
	while (read(fd, &ch, sizeof(ch)))
	{
		if(ch=='\n')
			number+=1;
	}
	close(fd);
	return number;
}

char* Reverse_string(char* str)
{
    int length=strlen(str);
    char ch;
    for(int i=0;i<length/2;i++)
    {
        ch=str[i];
        str[i]=str[length-(i+1)];
        str[length-(i+1)]=ch;	
    }	    
    return str;
}	

int main(int argc, char **argv)
{
	int fd, help, length, fd_orig[2], fd_rev[2], string_length[2];
	pid_t pid;
	char *str, ch;
	if (argc!=2)
	{
		fprintf(stderr, "Unsufficient number of arguments \n");
		exit(1);
	}
	pipe(fd_orig);
	pipe(fd_rev);
	pipe(string_length);
	if ((pid=fork())==-1)
	{
		fprintf(stderr, "Error: Failed to calling fork() \n");
		exit(1);				
	}
	else if (pid==0)
	{ 
		//сыновий процесс
		close(fd_orig[1]);
		close(fd_rev[0]);
		close(string_length[1]);
		while (read(string_length[0], &length, sizeof(length)))
		{
			str=(char*)malloc(length*sizeof(ch));
			read(fd_orig[0], str, length*sizeof(ch));
			str=Reverse_string(str);
			write(fd_rev[1], str, length*sizeof(ch));
			free(str);	    
		}	
		close(fd_orig[0]);
		close(fd_rev[1]);
		close(string_length[0]);
		exit(0);
	}
	else
	{
		//отцовский процесс
		close(fd_orig[0]);
		close(fd_rev[1]);
		close(string_length[0]);
		fd=open(argv[1], O_RDONLY, 0660);
		Open_file_error(fd);
		help=open("help", O_WRONLY|O_CREAT|O_TRUNC, 0660);
		Open_file_error(help);
		for(int i=0;i<Number_of_strings_in_file(argv[1]);i++)
		{
			str=Read_string(fd);
			if (strcmp(str, "\n"))
			{
				length=(strlen(str)+1);
				write(string_length[1], &length, sizeof(length));
				write(fd_orig[1], str, length*sizeof(ch));
				read(fd_rev[0], str, length*sizeof(ch));
				write(help, str, (length-1)*sizeof(ch));
				ch='\n';
				write(help, &ch, sizeof(ch));
				free(str);
			}
			else
			{
				ch='\n';
				write(help, &ch, sizeof(ch));
				free(str);		
			}
		}
		close(fd_orig[1]);
		close(fd_rev[0]);
		close(string_length[1]);
		close(fd);
		close(help);
		fd=open(argv[1], O_WRONLY|O_TRUNC, 0660);
		Open_file_error(fd);
		help=open("help", O_RDONLY, 0660);
		Open_file_error(help);
		while (read(help, &ch, sizeof(ch)))
		{
			write(fd, &ch, sizeof(ch));
		}
		close(fd);
		close(help);
		unlink("help");
		wait(NULL);
		exit(0);
	}
	return 0;
}
