/*
** EPITECH PROJECT, 2025
** corewar
** File description:
** usage.c
*/

#include <unistd.h>
#include "corewar.h"

// This is the default usage as given in the subject,
// We NEED to make an actual good one
static const char usage_text[] = "USAGE\n"
    "./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address]"
    " prog_name] ...\n"
    "DESCRIPTION\n"
    "-dump nbr_cycle dumps the memory after the nbr_cycle execution"
    " (if the round isn't already over) with the following format: 32"
    " bytes/line in hexadecimal (A0BCDEFE1DD3...)\n"
    "-n prog_number sets the next program's number. By default, the"
    " first free number in the parameter order\n"
    "-a load_address sets the next program's loading address. When no"
    " address is specified, optimize the addresses so that the processes"
    " are as far away from each other as possible. The addresses are"
    " MEM_SIZE modulo.\n";

void display_usage(void)
{
    write(STDOUT_FILENO, usage_text, sizeof(usage_text));
}
