#include "../include/shell-cmd.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell-parser.h"

#define EXT_SUCCESS 0
#define EXT_TOO_FEW_ARGS 1

Command* parse_args(char** arg_str, int num_args);
void free_args(Command* args);

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few arguments were passed");
        exit(EXT_TOO_FEW_ARGS);
    }

    Command* args = parse_args(argv, argc);

    printf("Command: %s\n", args->command);
    for (int i = 0; i < args->num_arguments; i++) {
        printf("Argument %d: %s\n", i + 1, args->arguments[i]);
    }

    /* free(args); */
    free_args(args);
    exit(EXT_SUCCESS);
}

