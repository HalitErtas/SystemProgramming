// This is color_utils.c file.
#include <stdio.h>
#include "color_utils.h"

void red() {
    printf("\033[1;31m");
}

void green() {
    printf("\033[1;32m");
}

void yellow() {
    printf("\033[1;33m");
}

void orange() {
    printf("\033[38;5;214m");
}

void coral() {
    printf("\033[38;5;209m");
}

void magenta() {
    printf("\033[35m");
}

void reset() {
    printf("\033[0m");
}
