// This is logger.h file.
#ifndef LOGGER_H
#define LOGGER_H

extern char log_message[1024];

void get_log_file_path();
void log_action(const char *message);
void log_and_print_error(const char *msg, int err_num);
void log_and_print_actions(const char *action_message);

#endif

