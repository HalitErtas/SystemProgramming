#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

#define PATH_MAX 2048

void list_dir_contents();
void go_one_folder_back();
void go_one_folder_forward(char* currentPath);
void create_folder();
void delete_folder(const char *filePath);

#endif