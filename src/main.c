#include "ansi_esc_codes.h"
#include "ls.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("   " UNDSCORE("inode") " " UNDSCORE("Permission") "  ");
    printf(UNDSCORE("Links") "       " UNDSCORE("Size") " ");
    printf(UNDSCORE("Blocks") "   " UNDSCORE("User") "    ");
    printf(UNDSCORE("Group") "   " UNDSCORE("Date Modified") " ");
    printf(UNDSCORE("Name") "\n");
    Option opt = {0};
    dir_read(".", &opt);
    // if (argc < 2) {
    //     dir_read(".", &opt);
    // } else if (argc == 2) {
    //     dir_read(argv[1], &opt); // NOT WORK
    // } else {
    //     printf("Usage: %s [OPTION]... [FILE]...\n", argv[0]);
    // }

    return 0;
}