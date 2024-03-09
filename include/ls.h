#include <dirent.h>
#include <sys/types.h>

#define EXT_FAILURE_CANT_ALLOCATE_MEMORY 2
#define EXT_FAILURE_CANT_OPEN_CURRENT_DIR 3

typedef struct {
    DIR* dir;
    struct dirent* dirrent;
} DirectoryInfo;

/* static DirectoryInfo* get_dir_info(char* path); */
void free_dir_info(DirectoryInfo* dir_info);

void list(char* path);
