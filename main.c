#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

void print_info(char *name, struct stat *stat)
{

    struct tm *tm = localtime(&stat->st_ctime);
    char buf[64];
    strftime(buf, 64, "%b %d %H:%M", tm);

    printf("%s %s\n", buf, name);
}

void dir_read(char *path)
{
    DIR *dir = opendir(path);
    struct dirent *file;
    if (dir)
    {
        while ((file = readdir(dir)) != NULL)
        {
            struct stat *buf = malloc(sizeof(struct stat));
            if (buf)
            {
                stat(file->d_name, buf);
                print_info(file->d_name, buf);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        dir_read(".");
    else if (argc == 2)
    {
        dir_read(argv[1]);
    }
    else
    {
        printf("Usage: %s [PATH]\n", argv[0]);
    }
    return 0;
}