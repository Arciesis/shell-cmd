#include "../include/shell-cmd.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* command;
    char** arguments;
    int num_arguments;
} Command;

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

/**
 * Function that parse the command and the potential argument(s) of a call to a Struct
 */
Command* parse_args(char** arg_str, int num_args) {
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

void free_args(Command* args) {
    for (int i = 0; i < args->num_arguments; i++) {
        free(args->arguments[i]);
    }
    free(args->arguments);
    free(args->command);
}
