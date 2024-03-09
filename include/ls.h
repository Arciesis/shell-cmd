#include <sys/types.h>
#include <dirent.h>

#define EXT_FAILURE_NO_CWD               2
#define EXT_FAILURE_CANT_OPEN_CWD       3

typedef struct {
    DIR* cwd_path;
    struct dirent* cwd;
} CurrentDirectoryInfo;

void free_list(DIR* cwd, struct dirent* current_dir);
CurrentDirectoryInfo* list_cwd(CurrentDirectoryInfo* directory_info);

// void free_long_list(DIR* cwd, struct dirent* current_dir); // TODO: implement this
void long_list();

