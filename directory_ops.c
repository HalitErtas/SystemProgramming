#include "directory_ops.h"
#include "color_utils.h"
#include "permissions.h"
#include "logger.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "common.h"


void list_dir_contents() {
    DIR* dirp;
    struct dirent* direntp;
    struct stat statstr;
    char buff[PATH_MAX];

    if (getcwd(buff, PATH_MAX) == NULL) {
        log_and_print_error("getcwd error", EINVAL);
        return;
    }

    dirp = opendir(buff);
    if (dirp != NULL) {
        printf("\nFile and directories in current path:\n");
        printf("%10s %10s %-15s\n","Permissions", "File Size", "File Name" );
        for (;;) {
            direntp = readdir(dirp);
            if (direntp == NULL) break;

            char filePath[PATH_MAX];
            int bytes_written = snprintf(filePath, sizeof(filePath), "%s/", buff);
            if (bytes_written < 0 || bytes_written >= sizeof(filePath)) {
                log_and_print_error("snprintf error", EOVERFLOW);
                continue;
            }
            strncat(filePath, direntp->d_name, sizeof(filePath) - strlen(filePath) - 1);

            if (stat(filePath, &statstr) == 0) {
                magenta();
                // Each file's permissions, size, and name.
                print_permissions(statstr.st_mode);
                printf("%10ld  ", statstr.st_size);
                printf("%3s\n", direntp->d_name);
                reset();
            } else {
                log_and_print_error("Stat error", EIO);
            }
        }
        closedir(dirp);
    } else {
        log_and_print_error("Could not open directory.", ENOENT);
    }
    log_and_print_actions("Folder listing successful.");
}

void go_one_folder_back() {
    if (chdir("..") != 0) {
        log_and_print_error("Could not go back to folder.", EIO);
    }
    log_and_print_actions("Folder has been changed.");
}

void go_one_folder_forward(char* currentPath) {
    char folderName[50];
    printf("Enter directory name to get into: ");
    scanf("%s", folderName);
    
    strcat(currentPath, "/");
    strcat(currentPath, folderName);
    
    if(chdir(currentPath) != 0) {
        sprintf(message, "Folder Name:%s could not found.", folderName);
        log_and_print_error(message, ENOENT);
    }
    else{
        sprintf(message, "Folder %s has been changed.", folderName);
        log_and_print_actions(message);
    }
}

void create_folder() {
    char folderName[50];

    printf("Enter the name of the folder to be created: ");
    scanf("%s", folderName);

    //mkdir ile klasör
    if (mkdir(folderName, 0755) == 0) {
        sprintf(message, "Folder Name:%s has been created succesfully", folderName);
        log_and_print_actions(message);
    } else {
        if (errno == EEXIST) {
            yellow();
            printf("Folder already exits: %s\n", folderName);
            reset();
        } else {
            log_and_print_error("Could not be created.", EIO);
        }
    }
}

void delete_folder(const char *filePath) {
    DIR *dir;
    struct dirent *direntp;
    
    printf("%s\n", filePath);
    
    dir = opendir(filePath);
    if (!dir) {
        log_and_print_error("Could not open the directory", ENOENT);
        return;
    }

    while ((direntp = readdir(dir)) != NULL) {
        char tmpFilePath[2048] = {0};

        if (strcmp(direntp->d_name, ".") == 0 || strcmp(direntp->d_name, "..") == 0)
            continue;

        snprintf(tmpFilePath, sizeof(tmpFilePath), "%s/%s", filePath, direntp->d_name);
        
        
        printf("Found entry: %s --->", tmpFilePath);

        struct stat statbuf;
        if (stat(tmpFilePath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                //rekursif çağrı burda olmalı
                delete_folder(tmpFilePath);
            } else if (S_ISREG(statbuf.st_mode)) {
                // Dosya ise sil
                sprintf(message, " It is file: %s | REMOVED SUCCESSFULLY!", direntp->d_name);
                log_and_print_actions(message);
                if (remove(tmpFilePath) != 0) {
                    log_and_print_error("Could not delete folder", EIO);
                }
            }
        } else {
            log_and_print_error("You do not have permission to delete folder", EACCES);
        }
    }

    closedir(dir);

    if (rmdir(filePath) != 0) {
        log_and_print_error("Could not delete the directory", EIO);
    }
    
    sprintf(message, "Folder Name:%s has been succesfully deleted", filePath);
    log_and_print_actions(message);
}

