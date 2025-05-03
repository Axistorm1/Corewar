/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** make sure any memory buffer can be parsed and not crash
*/

#include <criterion/criterion.h>
#include "parsing.h"
#include "structures.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>

#define BUFFER_SIZE 20

void print_buffer(const uint8_t *buffer) {
    for (int i = 0; i < BUFFER_SIZE; i++) {
        printf("%02X", buffer[i]);
    }
    printf("\n");
}

Test(parsing, analyze_memory)
{
    uint8_t buffer[BUFFER_SIZE] = {0};
    instruction_t *ptr = NULL;

    for (uint64_t i = 0; i < UINT64_MAX; i++) {
        arc4random_buf(buffer, BUFFER_SIZE);
        //print_buffer(buffer);
        ptr = analyze_memory(buffer);
        //print_instruction_data(ptr);
        //printf("%lu/%lu\n", i, UINT64_MAX);
        if (i > 20000000)
            break;
    }
}
