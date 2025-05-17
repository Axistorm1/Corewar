#include "parsing.h"
#include "utils.h"

// each 0xFF is the least signifant part of the value
unsigned int swap_endian(unsigned int num)
{
    return ((num >> BYTE * 3) & 0xFF) | ((num >> BYTE) & 0xFF00) |
           ((num << BYTE) & 0xFF0000) | ((num << BYTE * 3) & 0xFF000000);
}
