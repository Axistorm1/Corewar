/*
** EPITECH PROJECT, 2025
** header
** File description:
** header
*/
#include "../../include/op.h"
#include "../../include/corewar.h"
#include <stddef.h>
#include <stdio.h>
int parse_champions(
      parsing_data_t *parse_data)
{
    FILE *fptr = fopen("abel.cor", "r");
    char *buffer;
    size_t size = 0;
    ssize_t bytes_read = 0;

    bytes_read = getline(&buffer, &size, fptr);
    printf("oui %d\n", buffer[136]);
   
    return 0;
}
