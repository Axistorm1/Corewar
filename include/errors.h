/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** errors.h
*/

#ifndef ERRORS_H_
    #define ERRORS_H_

    #include <stdio.h>

enum error_codes {
    BAD_ARGUMENT,
    BAD_VALUE,
    MISSING_CHAMPION,
    FILE_NOT_FOUND,
    EMPTY_FILE,
};

    #define WARNINGS_START 100

enum warning_codes {
    NO,
};

void *write_error(
    int error_code,
    const char *before, ssize_t number);

#endif /* ERRORS_H_ */
