#include "../include/ls.h"

#include <dirent.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

static DirectoryInfo* get_dir_info(char* path);
static FileInfo* get_file_info(char* path);

static DirectoryInfo* get_dir_info(char* path) {
    DIR* current_dir = opendir(path);
    if (current_dir == NULL) {
        perror("Cannot open current Directory!");
        exit(EXT_FAILURE_CANT_OPEN_CURRENT_DIR);
    }

    struct dirent* entry = NULL;
    entry = readdir(current_dir);

    DirectoryInfo* dir_info = (DirectoryInfo*)malloc(sizeof(DirectoryInfo));
    if (dir_info == NULL) {
        perror("Can't allocate memory for the directory");
        exit(EXT_FAILURE_CANT_ALLOCATE_MEMORY);
    }

    dir_info->dir = current_dir;
    dir_info->dirrent = entry;

    return dir_info;
}

static FileInfo* get_file_info(char* path) {
    FileInfo* file_info = (FileInfo*)malloc(sizeof(FileInfo));

    char* file_basename = basename(path);

    char* perms = (char*)malloc(sizeof(char) * 11);
    file_info->permissions = (char*)malloc(sizeof(char) * 11);

    struct stat file_stat;

    file_info->name = (char*)malloc(sizeof(char) * (strlen(file_basename) + 1));
    file_info->name = strcpy(file_info->name, file_basename);

    file_info->type = (char*)malloc(sizeof(char) * 16);
    if (stat(path, &file_stat) == -1) {
        perror("Can't stat file");
        exit(EXT_FAILURE_CANT_STAT_FILE);
    }

    if (S_ISDIR(file_stat.st_mode)) {
        file_info->type = strcpy(file_info->type, "d");
    } else if (S_ISLNK(file_stat.st_mode)) {
        file_info->type = strcpy(file_info->type, "l");
    } else if (S_ISREG(file_stat.st_mode)) {
        file_info->type = strcpy(file_info->type, "-");
        file_info->size = file_stat.st_size / 1024;
    } else {
        file_info->type = strcpy(file_info->type, "?");
    }

    mode_t current_mode = umask(0);
    umask(current_mode);

    if (current_mode & S_IRUSR) {
        perms[0] = 'r';
    } else {
        perms[0] = '-';
    }

    if (current_mode & S_IWUSR) {
        perms[1] = 'w';
    } else {
        perms[1] = '-';
    }

    if (current_mode & S_IXUSR) {
        perms[2] = 'x';
    } else {
        perms[2] = '-';
    }

    if (current_mode & S_IRGRP) {
        perms[3] = 'r';
    } else {
        perms[3] = '-';
    }

    if (current_mode & S_IWGRP) {
        perms[4] = 'w';
    } else {
        perms[4] = '-';
    }

    if (current_mode & S_IXGRP) {
        perms[5] = 'x';
    } else {
        perms[5] = '-';
    }

    if (current_mode & S_IROTH) {
        perms[6] = 'r';
    } else {
        perms[6] = '-';
    }

    if (current_mode & S_IWOTH) {
        perms[7] = 'w';
    } else {
        perms[7] = '-';
    }

    if (current_mode & S_IXOTH) {
        perms[8] = 'x';
    } else {
        perms[8] = '-';
    }

    perms[9] = '.';
    perms[10] = '\0';

    file_info->permissions = strcpy(file_info->permissions, perms);

    free(file_basename);
    free(perms);
    return file_info;
}

void free_dir_info(DirectoryInfo* dir_info) {
    closedir(dir_info->dir);
    free(dir_info->dirrent);
    free(dir_info);
}

void free_file_info(FileInfo* file_info) {
    free(file_info->name);
    free(file_info->type);
    free(file_info->permissions);
    free(file_info);
}

void list(char* path) {
        DirectoryInfo* dir_info = get_dir_info(path);

    while ((dir_info->dirrent = readdir(dir_info->dir)) != NULL) {
        printf("%s\n", dir_info->dirrent->d_name);
    }

    free_dir_info(dir_info);
}

void list_long(char* path) {
    DirectoryInfo* dir_info = get_dir_info(path);
    FileInfo* file_info = malloc(sizeof(FileInfo));

    while ((dir_info->dirrent = readdir(dir_info->dir)) != NULL) {
        file_info = get_file_info(dir_info->dirrent->d_name);
        printf("%s %s %i %s\n", file_info->permissions, file_info->type, file_info->size,
               file_info->name);
    }

    free_file_info(file_info);
    free_dir_info(dir_info);
}
