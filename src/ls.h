#pragma once
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
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

void print_info(char* name, struct stat* stat, Option option);
void dir_read(char* path, Option* option);
char const* spermission(mode_t mode);