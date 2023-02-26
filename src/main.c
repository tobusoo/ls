#include "ansi_esc_codes.h"
#include "arguments.h"
#include "ls.h"
#include <stdio.h>

const char* argp_program_version = "app 0.0.1";
char doc[] = "documentation...";
const char* argp_program_bug_address = "<chppppr@yandex.ru>";
char args_doc[] = "[PATH]";
struct argp_option options[] = {
        {"all", 'a', 0, 0, "Show hidden files"},
        {0, 'A', 0, 0, "Don't show . and .. directories"},
        {"long", 'l', 0, 0, "Use a long listing format"},
        {"group", 'g', 0, 0, "list each file's group"},
        {"inode", 'i', 0, 0, "list each file's inode number"},
        {"bloks", 'B', 0, 0, "list each file's number of file system blocks"},
        {"size", 's', 0, 0, "list each file's size"},
        {"date", 'd', 0, 0, "list each file's modified date"},
        {"permission", 'p', 0, 0, "list each file's permission"},
        {"user", 'u', 0, 0, "list each file's user"},
        {"full", 'f', 0, 0, "show full information"},
        {0},
};

static struct argp argp = {options, parse_opt, args_doc, doc};

int main(int argc, char* argv[])
{
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

    dir_read(&arguments);

    return 0;
}