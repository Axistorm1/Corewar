#include <criterion/criterion.h>
#include "parsing.h"
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>

#define BUFFER_SIZE 14

Test(parsing, analyze_memory)
{
    uint8_t buffer[BUFFER_SIZE] = {0};

    for (uint64_t i = 0; i < 500000; i++) {
        arc4random_buf(buffer, BUFFER_SIZE);
        analyze_memory(buffer);
    }
}
