#include <stdlib.h>
#include <string.h>

#include "../include/shell-parser.h"

/**
 * Function that parse the command and the potential argument(s) of a call to a Struct
 */
extern Command* parse_args(char** arg_str, int num_args) {
    Command* args = malloc(sizeof(Command));
    const int default_args_num = 4;
    int args_proccessed;

    // Dynamically allocate memory for arguments
    char** commands_args = malloc(sizeof(char*) * default_args_num);
    char* current_arg;

    for (args_proccessed = 1; args_proccessed < num_args; args_proccessed++) {
        // Create a copy of the argument string
        char* copied_arg = strdup(arg_str[args_proccessed]);

        if (args_proccessed == 1) {
            // Allocate memory for the first argument, if proccesed_arg == 1 then
            // its the first tim we loop hence it's the command !
            // because proccessed_args = 0 is the name of the program
            args->command = copied_arg;
        } else {
            current_arg = copied_arg;
            // Reallocate memory for arguments if needed
            if (args_proccessed >= default_args_num) {
                void* tmp = realloc(commands_args, sizeof(char*) * (args_proccessed + 1));
                if (NULL == tmp) {
                    free(tmp);  // TODO: need a better way to handle this error !
                } else {
                    commands_args = tmp;
                }
            }
            // Assign the current argument, since the first args_proccessed is the program and the
            // second is the command we need to -2 it
            commands_args[args_proccessed - 2] = current_arg;
        }
    }

    // Asiigne the last variables of the struct
    args->arguments = commands_args;
    // Same as above for the -2
    args->num_arguments = (args_proccessed - 2);
    return args;
}

extern void free_args(Command* args) {
    for (int i = 0; i < args->num_arguments; i++) {
        free(args->arguments[i]);
    }
    free(args->arguments);
    free(args->command);
}
