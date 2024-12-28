// This is file_ops.c file.
#include "file_ops.h"
#include "color_utils.h"
#include "logger.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include "common.h"

void read_file() {
    char fileName[50];
    char buff[PATH_MAX];
    int fd, sz;
    struct stat fs;
    int r;
    char* c = (char*)malloc(1024 * sizeof(char));

    if (!c) {
        log_and_print_error("Memory allocation error", ENOMEM);
        return;
    }

    printf("Enter the the file name to be read: ");
    scanf("%s", fileName);

    if (getcwd(buff, PATH_MAX) == NULL) {
        log_and_print_error("getcwd error", EINVAL);
        free(c);
        return;
    }

    strcat(buff, "/");
    strcat(buff, fileName);
    
    r = stat(buff, &fs);
    if(r == -1){
        sprintf(message, "Do not have permission to read %s file", fileName);
        log_and_print_error(message, EACCES);
        return;
    }
    
    fd = open(buff, O_RDONLY);
    if (fd < 0) {
        log_and_print_error("Folder could not opened. Please enter valid folder name", ENOENT);
        free(c);
        return;
    }

    sz = read(fd, c, 1024);
    if (sz < 0) {
        log_and_print_error("File reading error", EIO);

        perror("File reading error");
    } else if (sz == 0) {
        printf("Folder empty.\n");
    } else {
        c[sz] = '\0';
        sprintf(message, "File read %s (%d bytes)", fileName, sz);
        log_and_print_actions(message);
        printf("\n----- File Content (%s) -----\n", fileName);
        printf("%s\n", c);
    }

    close(fd);
    free(c);
}

void write_file() {
    char fileName[50];
    char buff[PATH_MAX];
    char input[1024];
    int fd, sz, flags;
    struct stat fs;
    int r;

    printf("Enter the name of the file to be written: ");
    scanf("%s", fileName);

    char choice;
    do {
        printf("If the file exists and will be overwritten (y), if not, will be created (n): ");
        scanf(" %c", &choice);

        if (choice != 'y' && choice != 'n') {
            printf("Invalid choice! Please enter 'y' or 'n'.\n");
        }
    } while (choice != 'y' && choice != 'n');
    flags = (choice == 'y') ? (O_WRONLY | O_TRUNC) : (O_WRONLY | O_CREAT | O_TRUNC);

    if (getcwd(buff, PATH_MAX) == NULL) {
        log_and_print_error("getcwd error", EINVAL);
        return;
    }

    strcat(buff, "/");
    strcat(buff, fileName);

    
    r = stat(buff, &fs);
    if(r == -1){
        log_and_print_error("Do no have permission to read the file.", EACCES);
        return;
    }
    
    fd = open(buff, flags, 0644);
    if (fd < 0) {
        log_and_print_error("The file could not be opened or created.", EIO);
        return;
    }

    printf("Enter the text to be written to the file: ");
    getchar();
    fgets(input, 1024, stdin);

    sz = write(fd, input, strlen(input));
    if (sz < 0) {
        log_and_print_error("File writing error", EIO);
    } else {
        sprintf(message, "Written file %s (%d bytes)", fileName, sz);
        log_and_print_actions(message);
        printf("\n--- File Content (%s) ---\n",fileName);
        printf("%s\n", input);
    }

    close(fd);
}

void create_file() {
    char file_name[20];
    printf("Enter the name of the file to be created: ");
    scanf("%s", file_name);
    
    int fd = creat(file_name, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH); // Kullanıcı için okuma/yazma, grup ve diğerleri için okuma izinleri
    if (fd == -1) {
        log_and_print_error("File creation failed", EIO);
        return;
    }

    sprintf(message,"File created successfully: %s\n", file_name);
    log_and_print_actions(message);

    close(fd);
}

void delete_file() {
    char file_name[20];
    printf("Enter the name of the file to be deleted: ");
    scanf("%s", file_name);
    
    if (unlink(file_name) == -1) {
        log_and_print_error("File could not be deleted", EIO);
        return;
    }
    
    sprintf(message, "File deleted successfully: %s\n", file_name);
    log_and_print_actions(message);
}