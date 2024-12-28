// This is logger.c file.
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

char log_message[256];
extern char log_file_path[512];


void get_log_file_path(){
    char dir[512];
    getcwd(dir, sizeof(dir));
    
    snprintf(log_file_path, sizeof(dir), "%s/../Log/log.txt", dir);
}


//write message to the log.txt file
void log_action(const char *message) {
    FILE *log_file = fopen(log_file_path, "a");
    if (log_file == NULL) {
        perror("Could not open log file.");
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    timestamp[strlen(timestamp) - 1] = '\0';

    fprintf(log_file, "[%s] %s\n", timestamp, message);
    fclose(log_file);
}

void log_and_print_error(const char *msg, int err_num) {
    char *error_msg = strerror(err_num);

    red();
    printf("%s: %s\n", msg, error_msg);
    reset();

    snprintf(log_message, sizeof(log_message), "Error - %s: %s (Kod: %d)", msg, error_msg, err_num);
    log_action(log_message);
}

void log_and_print_actions(const char *action_message){
    
    green();
    printf("%s\n", action_message);
    reset();
    
    snprintf(log_message, sizeof(log_message), "Success - %s", action_message);
    
    log_action(log_message);
}
