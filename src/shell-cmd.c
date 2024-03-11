#include "../include/shell-cmd.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/shell-parser.h"
#include "../include/ls.h"

#define EXT_SUCCESS 0
#define EXT_TOO_FEW_ARGS 1

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Too few arguments were passed");
        exit(EXT_TOO_FEW_ARGS);
    }

    Input* args = parse_command(argv, argc);

    printf("Input: %s\n", args->command);
    for (int i = 0; i < args->num_arguments; i++) {
        printf("Argument %d: %s\n", i + 1, args->arguments[i]);
    }

    const char* ls_cmd = "ls";
    if (0 == strcmp(args->command, ls_cmd)) {
        char* path = "";
        if (args->arguments[0] == NULL) {
            path = ".";
        } else {
            path = args->arguments[0];
        }

        if (NULL == args->arguments[1]) {
            list(path);
        } else if (0 == strcmp(args->arguments[1], "-l")) {
            if (NULL == args->arguments[2]) {
                list_long(path);
            } else {
                list_long(args->arguments[2]);
            }
        } else {
            perror("An unknown argument has been passed");
            exit(EXT_FAILURE_UNKNOWN_ARGUMENT);
        }

    }

    /* free(args); */
    free_command(args);
    exit(EXT_SUCCESS);
}
