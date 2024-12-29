// This is permissions.h file.
#ifndef PERMISSIONS_OPS_H
#define PERMISSIONS_OPS_H

#include <sys/types.h>
#include <sys/stat.h> 

void print_permissions(mode_t mode);
void change_permissions();

#endif
