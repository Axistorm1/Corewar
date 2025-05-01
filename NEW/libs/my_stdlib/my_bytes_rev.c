/*
** EPITECH PROJECT, 2025
** my_stdlib
** File description:
** reverses the bits of a memory block
*/

#include "my_stdlib.h"
#include "../my_string/my_string.h"
#include <stdint.h>
#include <unistd.h>

/*
** How does this black magic work? Easy!
**
** This is our initial byte:  01000101
** The final byte we want is: 10100010
**
** EXPLANATION:
**                              COPY   INITIAL
** Create a new empty byte:   00000000 01000101
** Copy last bit of initial:  00000001 01000101
** Move our copy to the left: 00000010 01000101
** Move initial to the right: 00000010 00100010
** Repeat!
**
** ~~That's the theory at least~~
*/
static unsigned char rev_one_byte(uint8_t byte)
{
    uint8_t reversed = 0;

    for (my_size_t current_byte = 0; current_byte < 8; current_byte++) {
        reversed <<= 1;
        reversed |= (byte & 1);
        byte >>= 1;
    }
    return reversed;
}

static unsigned int rev_four_bytes(uint32_t bytes)
{
    uint32_t reversed = 0;

    for (my_size_t current_byte = 0; current_byte < 32; current_byte++) {
        reversed <<= 1;
        reversed |= (bytes & 1);
        bytes >>= 1;
    }
    return reversed;
}

static unsigned long int rev_eight_bytes(uint64_t bytes)
{
    uint64_t reversed = 0;

    for (my_size_t i = 0; i < 64; i++) {
        reversed <<= 1;
        reversed |= (bytes & 1);
        bytes >>= 1;
    }
    return reversed;
}

// bytes must either be 1 (8 bits), 4 (32) bits or 8 (64 bits)
// Nothing else is accepted!
void *my_bytes_rev(void *mem, my_size_t bytes)
{
    uint8_t tmp_one = 0;
    uint32_t tmp_four = 0;
    uint64_t tmp_eight = 0;

    if (bytes == 1) {
        tmp_one = rev_one_byte(*(uint8_t *)mem);
        return my_memcpy(mem, &tmp_one, 1);
    }
    if (bytes == 4) {
        tmp_four = rev_four_bytes(*(uint32_t *)mem);
        return my_memcpy(mem, &tmp_four, 4);
    }
    if (bytes == 8) {
        tmp_eight = rev_eight_bytes(*(uint64_t *)mem);
        return my_memcpy(mem, &tmp_eight, 8);
    }
    return MY_NULL;
}
