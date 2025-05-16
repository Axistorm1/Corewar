/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** my_puts.c
*/

#include "arena.h"
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
    char buffer[BUFFER_SIZE];

    my_memset(buffer, 0, BUFFER_SIZE);
    my_ltoa(nb, buffer, BASE_TEN);
    return write(STDOUT_FILENO, buffer, my_strlen(buffer));
}

ssize_t my_puts_hexa(ssize_t nb, size_t leading_zeros)
{
    char buffer[BUFFER_SIZE];
    char zeros[leading_zeros];

    my_memset(zeros, '0', leading_zeros);
    my_memset(buffer, 0, BUFFER_SIZE);
    my_ltoa(nb, buffer, BASE_HEXA);
    for (int i = 0; buffer[i]; i++)
        buffer[i] = (char)my_toupper(buffer[i]);
    write(STDOUT_FILENO, zeros, leading_zeros - my_strlen(buffer));
    write(STDOUT_FILENO, buffer, my_strlen(buffer));
    return 0;
}
