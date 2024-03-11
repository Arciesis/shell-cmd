#include <dirent.h>
#include <sys/types.h>
#include <wchar.h>

#define EXT_FAILURE_CANT_ALLOCATE_MEMORY 2
#define EXT_FAILURE_CANT_OPEN_CURRENT_DIR 3
#define EXT_FAILURE_CANT_STAT_FILE 4

typedef struct {
    DIR* dir;
    struct dirent* dirrent;
} DirectoryInfo;

typedef struct {
    char* name;
    char* type;
    char* permissions;
    int size;
} FileInfo;

/* static DirectoryInfo* get_dir_info(char* path); */
void free_dir_info(DirectoryInfo* dir_info);
void free_file_info(FileInfo* file_info);

void list_long(char* path);
void list(char* path);
