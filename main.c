// This is main.c file.
#include "file_ops.h"
#include "color_utils.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>

char log_file_path[512];
char log_message[1024]; 
char message[1024];

void print_centered(const char* text);

int main() {
        
    char currentPath[2048];
    int choice;
    get_log_file_path(); // centralized logging and puts every user interactions into /Log/log.txt file
    
    
    while (1) {
        char fileName[50] = {0}; // case 5 (delete_folder)
        
        yellow();
        print_centered("======== Menu ========");
        print_centered("1.  List files and directories in current path      ");
        print_centered("2.  Go one directory back                           ");
        print_centered("3.  Go one directory forward                        ");
        print_centered("4.  Create directory                                ");
        print_centered("5.  Delete directory                                ");
        print_centered("6.  Find a string any specific directory path       ");
        print_centered("7.  Change a file and directory permissions         ");
        print_centered("8.  Read a file                                     ");
        print_centered("9.  Write a file (truncate then write)              ");
        print_centered("10. Create file                                     ");
        print_centered("11. Delete file                                     ");
        print_centered("12. Copy file                                       ");
        print_centered("13. EXIT                                            ");
        print_centered("========================");
        coral();
        printf("current path: %s\n", getcwd(currentPath, 2048));
        reset();
        printf(">> ");
        
        if (scanf("%d", &choice) != 1) {
            log_and_print_error("Invalid input. Please prompt any given number.", 0);

            while (getchar() != '\n');

            continue; // go back Menu
        }

        switch (choice) {
            case 1:
                list_dir_contents();
                break;
            case 2:
                go_one_folder_back();
                break;
            case 3:
                go_one_folder_forward(currentPath);
                break;
            case 4:
                create_folder();
                break;
            case 5:
                printf("Prompt a directory name to delete:");
                scanf("%s", fileName);
                strcat(currentPath,"/");
                strcat(currentPath,fileName);
                delete_folder(currentPath); // recursion yapabilmek için fonksiyon içerisinde path alamadım :(
                break;
            case 6:
                search_string_in_folder();
                break;
            case 7:
                change_permissions();
                break;
            case 8:
                read_file();
                break;
            case 9:
                write_file();
                break;
            case 10:
                create_file();
                break;
            case 11:
                delete_file();
                break;
            case 12:
                copy_file_to_directory();
                break;
            case 13:
                printf("EXITING...\n");
                exit(0);
            default:
                printf("Invliad prompt. Try again.\n");
                break;
        }
    }

    return 0;
}

void print_centered(const char* text) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int terminal_width = w.ws_col;

    int text_length = strlen(text);
    int padding = (terminal_width - text_length) / 2;
    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }
    printf("%s\n", text);
}
