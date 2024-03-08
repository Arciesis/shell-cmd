typedef struct {
    char* command;
    char** arguments;
    int num_arguments;
} Input;

typedef enum {
    long_args,
    short_args,
} Args_version;

extern Input* parse_command(char** arg_str, int num_args);
extern void free_command(Input* input);
void parse_args(Input* command);
