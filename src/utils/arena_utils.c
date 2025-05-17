#include "arena.h"
#include "op.h"
#include "parsing.h"
#include "structures.h"
#include "utils.h"

void write4_to_arena(arena_t *arena, byte2_t adress, byte4_t data,
                     byte4_t prog_number)
{
    arena->memory[adress % MEM_SIZE]       = (byte1_t)(data >> BYTE * 3) & LSB;
    arena->memory[(adress + 1) % MEM_SIZE] = (data >> BYTE * 2) & LSB;
    arena->memory[(adress + 2) % MEM_SIZE] = (data >> BYTE) & LSB;
    arena->memory[(adress + 3) % MEM_SIZE] = data & LSB;
    arena->ownership_map[adress]           = prog_number;
    arena->ownership_map[(adress + 1) % MEM_SIZE] = prog_number;
    arena->ownership_map[(adress + 2) % MEM_SIZE] = prog_number;
    arena->ownership_map[(adress + 3) % MEM_SIZE] = prog_number;
}

byte2_t update_program_counter(byte2_t program_counter, sbyte2_t n)
{
    int new            = program_counter + n;
    int circular_index = (new % MEM_SIZE + MEM_SIZE) % MEM_SIZE;

    return (byte2_t)circular_index;
}
