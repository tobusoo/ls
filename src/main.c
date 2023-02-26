#include "ansi_esc_codes.h"
#include "arguments.h"
#include "ls.h"
#include <stdio.h>

const char* argp_program_version = "app 0.0.1";
char doc[] = "documentation...";
const char* argp_program_bug_address = "<chppppr@yandex.ru>";
char args_doc[] = "[PATH]";
struct argp_option options[] = {
        {0, 'a', 0, 0, "Show hidden files"},
        {0, 'A', 0, 0, "Don't show . and .."},
        {0, 'l', 0, 0, "Use a long listing format"},
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