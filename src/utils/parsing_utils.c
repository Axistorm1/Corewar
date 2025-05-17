#include "structures.h"
#include "parsing.h"

int verify_coding_byte(instruction_t *instruction)
{
    int inst_no_coding[] = {LIVE, ZJMP, FORK, LFORK};

    for (int i = 0; i != CODING_NBR; i++)
        if (instruction->op_code == inst_no_coding[i]) {
            instruction->coding_byte = 0;
            return 1;
        }
    return 2;
}

void int_to_bin(
    int n,
    char output[9])
{
    for (int i = 7; i >= 0; i--)
        output[7 - i] = (n & (1 << i)) ? '1' : '0';
    output[8] = '\0';
}
