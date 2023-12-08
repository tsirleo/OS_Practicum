#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

void Double(char *st, int n, int m)
{
    int fp, cur_pos_fp, cur_pos_st, k=0, length=0, number=0;
    char ch;
    if ((fp=open(st, O_RDWR, 0660))!=-1)
    {
        cur_pos=lseek(fp, 0, SEEK_CUR);
        while (k<n)
        {
            read(fp, &ch, sizeof(ch);
            if (ch=='\n')
            {
                if(length>m)
                {
                    cur_pos_fp=lseek(fp, 0, SEEK_CUR);
                    for(int i=0;i<length;i++)
                    {
                        read(
                    }
                    lseek(fp, cur_pos_fp, SEEK_SET);
                }
                length=0;
            }
            else
            {
                length+=1;
            }
        }
    }
    else
    {
        fprintf(stderr, "Open file error");
        close(fp);
        exit(1);
    }
    close(fp);
}

int main(int argc, char **argv)
{
    struct stat info;
    int fp, m, n, k=0;
    char ch;
    if (argc<4)
    {
        fprintf(stderr, "Unsufficient number of parameters");
        exit(1);
    }
    sscanf(argv[2],"%d", &n);
    sscanf(argv[3],"%d", &m);
    if ((fp=open(argv[1], O_WRONLY, 0660))==-1)
    {
        close(fp);
        if ((fp=open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0660))!=-1)
        {
            while (k<n)
            {
                read(0, &ch, sizeof(ch));
                if (ch=='\n')
                {
                    k+=1;
                }
                write(fp, &ch, sizeof(ch)); 
            }
            close(fp);
        }
        else
        {
            fprintf(stderr, "Open file error");
            close(fp);
            exit(1);
        }
    }
    else
    {
        fp=open(argv[1], O_RDWR, 0660);
    }
    stat(argv[1], &info);
    printf("Index descriptor №: %ld \n", info.st_ino);
    printf("File length: %ld \n", info.st_size);
    printf("Number of hard links: %lu \n", info.st_nlink);
    close(fp);
    Double(argv[1], n, m);
    return 0;
}

