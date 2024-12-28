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
