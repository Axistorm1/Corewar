/*
** EPITECH PROJECT, 2025
** header
** File description:
** header
*/
#include "../../../include/op.h"
#include "../../../include/corewar.h"
#include "../../../include/parsing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

void int_to_bin(
    int n,
    char output[9])
{
    for (int i = 7; i >= 0; i--) {
        output[7 - i] = (n & (1 << i)) ? '1' : '0';
    }
    output[8] = '\0';
}
