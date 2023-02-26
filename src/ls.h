#pragma once
#include "arguments.h"
#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

void print_info(char* name, struct stat* stat, Arg option);
void dir_read(Arg* option);
char const* spermission(mode_t mode);