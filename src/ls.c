#include "../include/ls.h"

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static DirectoryInfo* get_dir_info(char* path);

static DirectoryInfo* get_dir_info(char* path) {
    DIR* current_dir = opendir(path);
    if (current_dir == NULL) {
        perror("Cannot open current Directory!");
        exit(EXT_FAILURE_CANT_OPEN_CURRENT_DIR);
    }

    struct dirent* entry = NULL;
    entry = readdir(current_dir);

    DirectoryInfo* dir_info = malloc(sizeof(DirectoryInfo));
    if (dir_info == NULL) {
        perror("Can't allocate memory for the directory");
        exit(EXT_FAILURE_CANT_ALLOCATE_MEMORY);
    }

    dir_info->dir = current_dir;
    dir_info->dirrent = entry;

    return dir_info;
}

void free_dir_info(DirectoryInfo* dir_info) {
    closedir(dir_info->dir);
    free(dir_info->dirrent);
    free(dir_info);
}

void list(char* path) { 
    DirectoryInfo* dir_info = get_dir_info(path);

    while ((dir_info->dirrent = readdir(dir_info->dir)) != NULL) {
        printf("%s\n", dir_info->dirrent->d_name);
    }

    free_dir_info(dir_info);
}

