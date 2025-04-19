/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** my_puts.c
*/

#include "my_stdlib.h"
#include "my_string.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

ssize_t my_puts(char *str)
{
    size_t len = my_strlen(str);
    char new[len + 2];

    my_memcpy(new, str, len);
    new[len] = '\n';
    new[len + 1] = '\0';
    return write(STDOUT_FILENO, new, len + 1);
}

ssize_t my_puts_nb(ssize_t nb)
{
    char buffer[20];

    my_memset(buffer, 0, 20);
    my_ltoa(nb, buffer, 10);
    return write(STDOUT_FILENO, buffer, my_strlen(buffer));
}

ssize_t my_puts_multiple(size_t n, ...)
{
    va_list args;
    char *tmp = NULL;
    ssize_t wrote_bytes = 0;

    va_start(args, n);
    for (size_t i = 0; i < n - 1; i++) {
        tmp = va_arg(args, char *);
        wrote_bytes += write(STDOUT_FILENO, tmp, my_strlen(tmp));
        wrote_bytes += write(STDOUT_FILENO, " ", 1);
    }
    tmp = va_arg(args, char *);
    wrote_bytes += write(STDOUT_FILENO, tmp, my_strlen(tmp));
    wrote_bytes += write(STDOUT_FILENO, "\n", 1);
    va_end(args);
    return wrote_bytes;
}
