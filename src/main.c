#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

typedef struct option {
    unsigned int a : 1;
    unsigned int A : 1;
    unsigned int inode : 1;
    unsigned int link : 1;
    unsigned int block : 1;
    unsigned int user : 1;
    unsigned int group : 1;
    unsigned int perm : 1;
    unsigned int size : 1;
    unsigned int date : 1;
} Option;

char const* spermission(__mode_t mode)
{
    static char local_buff[16] = {0};
    int i = 0;

    // file type
    if (S_ISDIR(mode)) {
        local_buff[i] = 'd';
    } else if (S_ISREG(mode)) {
        local_buff[i] = '-';
    } else if (S_ISCHR(mode)) {
        local_buff[i] = 'c';
    } else if (S_ISBLK(mode)) {
        local_buff[i] = 'b';
    } else if (S_ISFIFO(mode)) {
        local_buff[i] = '?';
    } else if (S_ISLNK(mode)) {
        local_buff[i] = 'l';
    } else
        local_buff[i] = '?';
    i++;

    // user permissions
    if ((mode & S_IRUSR) == S_IRUSR)
        local_buff[i] = 'r';
    else
        local_buff[i] = '-';
    i++;
    if ((mode & S_IWUSR) == S_IWUSR)
        local_buff[i] = 'w';
    else
        local_buff[i] = '-';
    i++;
    if ((mode & S_IXUSR) == S_IXUSR)
        local_buff[i] = 'x';
    else
        local_buff[i] = '-';
    i++;
    // group permissions
    if ((mode & S_IRGRP) == S_IRGRP)
        local_buff[i] = 'r';
    else
        local_buff[i] = '-';
    i++;
    if ((mode & S_IWGRP) == S_IWGRP)
        local_buff[i] = 'w';
    else
        local_buff[i] = '-';
    i++;
    if ((mode & S_IXGRP) == S_IXGRP)
        local_buff[i] = 'x';
    else
        local_buff[i] = '-';
    i++;
    // other permissions
    if ((mode & S_IROTH) == S_IROTH)
        local_buff[i] = 'r';
    else
        local_buff[i] = '-';
    i++;
    if ((mode & S_IWOTH) == S_IWOTH)
        local_buff[i] = 'w';
    else
        local_buff[i] = '-';
    i++;
    if ((mode & S_IXOTH) == S_IXOTH)
        local_buff[i] = 'x';
    else
        local_buff[i] = '-';
    return local_buff;
}

char* size_to_str(off_t size)
{
    // pass
    return NULL;
}

void print_info(char* name, struct stat* stat, Option option)
{
    if (option.inode == 1) {
        printf("%8ld ", stat->st_ino);
    }

    if (option.perm == 1) {
        printf("%s  ", spermission(stat->st_mode));
    }

    if (option.link == 1) {
        printf("%5ld ", stat->st_nlink);
    }

    if (option.size == 1) {
        // char *str = size_to_str(stat->st_size);
        // printf("%5.5s", str);
        printf("%5ld ", stat->st_size);
    }

    if (option.block == 1) {
        printf("%6ld ", stat->st_blocks);
    }

    if (option.user == 1) {
        struct passwd* pwd;
        if ((pwd = getpwuid(stat->st_uid)) != NULL)
            printf("%-8.8s ", pwd->pw_name);
        else
            printf("%-8d ", stat->st_uid);
    }

    if (option.group == 1) {
        struct group* grp;
        if ((grp = getgrgid(stat->st_gid)) != NULL)
            printf("%-8.8s ", grp->gr_name);
        else
            printf("%-8d ", stat->st_gid);
    }

    if (option.date == 1) {
        struct tm* tm = localtime(&stat->st_ctime);
        char buf[64];
        strftime(buf, 64, "%d %b %H:%M", tm);
        printf("%s\t", buf);
    }

    printf("%s\n", name);
}

void dir_read(char* path, Option* option)
{
    DIR* dir = opendir(path);
    struct dirent* file;
    if (dir) {
        while ((file = readdir(dir)) != NULL) {
            if (option->a == 0 && option->A == 0) {
                if (strcmp(file->d_name, ".") == 0
                    || strcmp(file->d_name, "..") == 0)
                    continue;
                if (file->d_name[0] == '.')
                    continue;
            }
            struct stat* buf = malloc(sizeof(struct stat));
            if (buf) {
                stat(file->d_name, buf);
                Option opt = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
                print_info(file->d_name, buf, opt);
                free(buf);
            }
        }
    }
    free(dir);
}

int main(int argc, char* argv[])
{
    printf("   inode Permissions Links  Size Blocks   User    Group   Date "
           "Modified Name\n");
    Option opt = {0};
    if (argc < 2) {
        dir_read(".", &opt);
    } else if (argc == 2) {
        dir_read(argv[1], &opt);
    } else {
        printf("Usage: %s [OPTION]... [FILE]...\n", argv[0]);
    }

    return 0;
}