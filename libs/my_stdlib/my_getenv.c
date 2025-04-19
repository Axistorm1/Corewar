/*
** EPITECH PROJECT, 2025
** my_string
** File description:
** returns the asked value inside the environment variables
*/

#include "../my_string/my_string.h"
#include "my_stdlib.h"

extern char **environ;

char *my_getenv(const char *name)
{
    char *variable_str = MY_NULL;

    for (my_size_t variable = 0; environ[variable]; variable++)
        if (my_strstr(environ[variable], name))
            variable_str = environ[variable];
    if (!variable_str)
        return MY_NULL;
    return &variable_str[my_strcspn(variable_str, "=") + 1];
}
