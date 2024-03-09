#include "../include/ls.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// static

CurrentDirectoryInfo* list_cwd() {
    char* cwd_path = NULL;
    char* buf = NULL;
    size_t buf_size = 256;
    cwd_path = getcwd(buf, buf_size);

    if (cwd_path == NULL) {
        perror("Current Working Directory was not retrieve!");
        exit(EXT_FAILURE_NO_CWD);
    }

    DIR* cwd = opendir(cwd_path);
    if (cwd == NULL) {
        perror("Cannot open current Directory!");
        exit(EXT_FAILURE_CANT_OPEN_CWD);
    }

    struct dirent* entry;
    while ((entry = readdir(cwd)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    CurrentDirectoryInfo cwd_info = {cwd, entry};
    return &cwd_info;
    //  closedir(cwd);
    // free_list(cwd, entry);
}

void free_list(DIR* cwd, struct dirent* current_dirent) {
    free(cwd);
    free(current_dirent);
}

long_list() {}
