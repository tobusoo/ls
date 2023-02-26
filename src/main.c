#include "ansi_esc_codes.h"
#include "arguments.h"
#include "ls.h"
#include <stdio.h>

const char* argp_program_version = "app 0.0.1";
char doc[] = "documentation...";
const char* argp_program_bug_address = "<chppppr@yandex.ru>";
char args_doc[] = "[PATH]";
struct argp_option options[] = {
        {"idk", 'a', 0, 0, "Show hidden files"},
        {"idk2", 'A', 0, 0, "Don't show . and .."},
        {0},
};

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char* argv[])
{
    // printf("   " UNDSCORE("inode") " " UNDSCORE("Permission") "  ");
    // printf(UNDSCORE("Links") "       " UNDSCORE("Size") " ");
    // printf(UNDSCORE("Blocks") "   " UNDSCORE("User") "    ");
    // printf(UNDSCORE("Group") "   " UNDSCORE("Date Modified") " ");
    // printf(UNDSCORE("Name") "\n");

    Arg arguments;
    // set default settings
    arguments.path = ".";
    arguments.A = 0;
    arguments.a = 0;
    arguments.block = 0;
    arguments.date = 0;
    arguments.group = 0;
    arguments.inode = 0;
    arguments.link = 0;
    arguments.perm = 0;
    arguments.size = 0;
    arguments.user = 0;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);

    dir_read(".", &arguments);

    printf("\n");
    printf("path: %s\n", arguments.path);
    printf("a: %s\n", arguments.a ? "yes" : "no");
    printf("A: %s\n", arguments.A ? "yes" : "no");
    printf("inode: %s\t", arguments.inode ? "yes" : "no");
    printf("link: %s\t", arguments.link ? "yes" : "no");
    printf("block: %s\t", arguments.block ? "yes" : "no");
    printf("user: %s\t", arguments.user ? "yes" : "no");
    printf("group: %s\t", arguments.group ? "yes" : "no");
    printf("perm: %s\t", arguments.perm ? "yes" : "no");
    printf("size: %s\t", arguments.size ? "yes" : "no");
    printf("data: %s\n", arguments.date ? "yes" : "no");

    return 0;
}