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
