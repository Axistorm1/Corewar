/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** my_puts.c
*/

#include "my_stdlib.h"
#include "my_string.h"
#include "my_ctype.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

ssize_t my_puts(char *str)
{
    size_t len = my_strlen(str);
    char *new = malloc(sizeof(char) * (len + 2));
    ssize_t written_bytes = 0;

    my_memcpy(new, str, len);
    new[len] = '\n';
    new[len + 1] = '\0';
    written_bytes = write(STDOUT_FILENO, new, len + 1);
    free(new);
    return written_bytes;
}

ssize_t my_puts_nb(ssize_t nb)
{
    char buffer[20];

    my_memset(buffer, 0, 20);
    my_ltoa(nb, buffer, 10);
    return write(STDOUT_FILENO, buffer, my_strlen(buffer));
}

ssize_t my_puts_hexa(ssize_t nb, size_t leading_zeros)
{
    char buffer[20];
    char zeros[leading_zeros];

    my_memset(zeros, '0', leading_zeros);
    my_memset(buffer, 0, 20);
    my_ltoa(nb, buffer, 16);
    for (int i = 0; buffer[i]; i++)
        buffer[i] = (char)my_toupper(buffer[i]);
    write(STDOUT_FILENO, zeros, leading_zeros - my_strlen(buffer));
    write(STDOUT_FILENO, buffer, my_strlen(buffer));
    return 0;
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
