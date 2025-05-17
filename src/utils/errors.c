#include "errors.h"
#include <stdio.h>

static const char *const error_strings[] = {
    "Incorrect argument",
    "Incorrect value",
    "Champion file is missing",
    "No such file",
    "File is empty",
    "There must be at least one robot",
    "File is incorrect",
    "The file must be a .cor file and have a magic number",
    "Program too big for the arena",
    "Program number must be higher than 0",
    "There was an error placing the programs",
    "Program number must be lower than 65535",
    "Header is incorrect or too small",
};

static const char *const warning_strings[] = {
    "is lonely in the arena :( Consider finding him some friends",
    "cycle will never be reached (MAX: 4,733,960)",
    "The total memory amount of the programs is higher than the arena size"};

void *write_error(int error_code, const char *before, ssize_t number)
{
    const char *string = NULL;
    char       *color  = NULL;

    if (error_code < WARNINGS_START)
    {
        string = error_strings[error_code];
        color  = "\033[31m";
    }
    else
    {
        string = warning_strings[error_code - WARNINGS_START];
        color  = "\033[36m";
    }
    if (before)
        printf("%s%s: %s\033[0m\n", color, before, string);
    if (number != -1)
        printf("%s%ld: %s\033[0m\n", color, number, string);
    if (before && number != -1)
        printf("%s%s%ld: %s\033[0m\n", color, before, number, string);
    if (!before && number == -1)
        printf("%s%s\033[0m\n", color, string);
    return NULL;
}
