#include "ls.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("   inode Permissions Links      Size Blocks   User    Group   Date "
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