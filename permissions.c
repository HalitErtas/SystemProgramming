// This is permissions.c file.
#include "permissions.h"
#include "logger.h"
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "common.h"

void print_permissions(mode_t mode) {
    char perms[11];

    perms[0] = (S_ISDIR(mode)) ? 'd' : '-';

    // Owner permissions
    perms[1] = (mode & S_IRUSR) ? 'r' : '-';
    perms[2] = (mode & S_IWUSR) ? 'w' : '-';
    perms[3] = (mode & S_IXUSR) ? 'x' : '-';

    // Group permissions
    perms[4] = (mode & S_IRGRP) ? 'r' : '-';
    perms[5] = (mode & S_IWGRP) ? 'w' : '-';
    perms[6] = (mode & S_IXGRP) ? 'x' : '-';

    // Other permissions
    perms[7] = (mode & S_IROTH) ? 'r' : '-';
    perms[8] = (mode & S_IWOTH) ? 'w' : '-';
    perms[9] = (mode & S_IXOTH) ? 'x' : '-';

    perms[10] = '\0';

    printf("%s  ", perms);
}

void change_permissions() {
    char file_path[1024];
    char permission_input[10];
    mode_t new_permissions;

    printf("Enter the file or folder you want to change: ");
    scanf("%s", file_path);

    printf("Enter new permissions (for example 0755): ");
    scanf("%s", permission_input);

    char *endptr;
    new_permissions = strtol(permission_input, &endptr, 8); //octet conversion!!!
    if (*endptr != '\0' || new_permissions < 0 || new_permissions > 0777) {
        sprintf(message, "Invalid permission value: %s", permission_input);
        log_and_print_error(message, EINVAL);
        return;
    }

    if (chmod(file_path, new_permissions) == -1) {
        sprintf(message, "File: %s -> file permissions: %o", file_path, new_permissions);
        log_and_print_error(message, EINVAL);
        return;
    }
    
    sprintf(message, "Permissions changed successfully: %s -> %o\n", file_path, new_permissions);
    log_and_print_actions(message);
}
