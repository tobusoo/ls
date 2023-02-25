#include "ls.h"
#include <stdio.h>

static void size_to_str(off_t size);

char const* spermission(mode_t mode)
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
    char* str = malloc(11);
    double temp;

    if (size / 1024 == 0) {
        size %= 1024;
        sprintf(str, "%ldB", size);
    } else if (size / (1024 * 1024) == 0) {
        temp = (double)size / 1024;
        sprintf(str, "%.1lfKiB", temp);
    } else {
        temp = (double)size / (1024 * 1024);
        sprintf(str, "%.1lfMiB", temp);
    }
    return str;
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
        char* str = size_to_str(stat->st_size);
        printf("%9s ", str);
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
        printf("%s  ", buf);
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