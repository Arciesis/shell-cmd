typedef struct {
    char* command;
    char** arguments;
    int num_arguments;
} Command;


extern Command* parse_args(char** arg_str, int num_args);
extern void free_args(Command* args);
