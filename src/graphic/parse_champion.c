#include "op.h"
#include "parsing.h"
#include "structures.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

instruction_t **parse_champions(header_t *header, char *filename)
{
    FILE           *fptr = fopen(filename, "r");
    instruction_t **instructions =
        calloc((ulong)header->prog_size + 1, sizeof(instruction_t *));
    byte1_t buffer[15]  = {0};
    ssize_t current_pos = sizeof(header_t);
    ssize_t file_size   = 0;

    fseek(fptr, 0L, SEEK_END);
    file_size = ftell(fptr);
    rewind(fptr);
    for (int i = 0; i < header->prog_size && current_pos < file_size; i++)
    {
        if (fseek(fptr, current_pos, SEEK_SET) == -1)
            break;
        fread(buffer, 14, 1, fptr);
        instructions[i] = analyze_memory(buffer);
        current_pos += instructions[i]->size;
    }
    fclose(fptr);
    return instructions;
}
