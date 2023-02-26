#pragma once
#include <argp.h>

typedef struct arguments {
    char* path;
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
} Arg;

error_t parse_opt(int key, char* arg, struct argp_state* state);
