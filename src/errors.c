/*
** EPITECH PROJECT, 2025
** G-AIA-200-TLS-2-1-cuddle-pavel.de-wavrechin
** File description:
** cuddle
*/

#include "errors.h"
#include "my_string.h"
#include "utils.h"
#include <stdio.h>
#include <unistd.h>

static const char *const error_strings[] = {
    "Incorrect argument",
    "Incorrect value",
    "Champion file is missing",
    "No such file",
    "File is empty",
    "There must be at least one robot",
    "File is incorrect",
    "The file must be a .cor file and have a magic number",
    "Robot too big for the arena"
};

static const char *const warning_strings[] = {
    "is lonely in the arena :( Consider finding him some friends",
    "cycle will never be reached (MAX: 236,698)"
};

static void write_auxiliary(
    const char *before,
    ssize_t number)
{
    if (before) {
        write(STDOUT_FILENO, before, my_strlen(before));
        write(STDOUT_FILENO, ":", 1);
    }
    if (number != -1) {
        my_puts_nb(number);
        write(STDOUT_FILENO, ":", 1);
    }
    if (before || number != -1)
        write(STDOUT_FILENO, " ", 1);
}

void *write_error(
    int error_code,
    const char *before,
    ssize_t number)
{
    const char *string = NULL;

    if (error_code < WARNINGS_START) {
        string = error_strings[error_code];
        write(STDOUT_FILENO, "\033[31m", 5);
    } else {
        string = warning_strings[error_code - WARNINGS_START];
        write(STDOUT_FILENO, "\033[36m", 5);
    }
    write_auxiliary(before, number);
    write(STDOUT_FILENO, string, my_strlen(string));
    my_puts("\033[0m");
    return NULL;
}
