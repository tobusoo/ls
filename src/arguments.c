#include "arguments.h"
#include <stdlib.h>

// define a function which will parse the args.
error_t parse_opt(int key, char* arg, struct argp_state* state)
{
    struct arguments* arguments = state->input;
    switch (key) {
    case 'a':
        arguments->a = 1;
        break;

    case 'A':
        arguments->A = 1;
        break;

    case 'l':
        arguments->perm = 1;
        arguments->link = 1;
        arguments->user = 1;
        arguments->user = 1;
        arguments->size = 1;
        arguments->date = 1;
        break;

    case ARGP_KEY_ARG:
        if (state->arg_num >= 1) {
            argp_usage(state);
        }
        arguments->path = arg;
        break;

    default:
        return ARGP_ERR_UNKNOWN;
    }

    return 0;
}
