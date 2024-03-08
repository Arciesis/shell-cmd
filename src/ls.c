#include "../include/ls.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

void list_cwd() {
    char* cwd_path = NULL;
    char* buf = NULL;
    size_t buf_size = 256;
    cwd_path = getcwd(buf, buf_size);
    printf("cwd path => %s\n", cwd_path);

    if (cwd_path == NULL) {
        perror("Current Working Directory was not retrieve!");
        exit(EXIT_FAILURE);  // TODO: Make an error type for that error !
    }

    DIR* cwd = opendir(cwd_path);
    if (cwd == NULL) {
        perror("Cannot open current Directory!");
        exit(EXIT_FAILURE); // TODO: Make an error type for that error !
    }

    const struct dirent* entry;
    while ((entry = readdir(cwd)) != NULL) {
        printf("%u => %s\n", entry->d_type, entry->d_name);
    }

    closedir(cwd);
    free(cwd_path);
}

void free_list(DIR* cwd, struct dirent* current_dirent) {
    free(cwd);
    free(current_dirent);
}
