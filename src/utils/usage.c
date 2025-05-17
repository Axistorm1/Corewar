#include "corewar.h"
#include "utils.h"
#include <unistd.h>

// This is the default usage as given in the subject,
// We NEED to make an actual good one
// UPDATE FOR BONUS
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

static const char bonus_usage_text[] = "USAGE (Bonus)\n"
    "./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address]"
    " prog_name] ...\n\n"
    ""
    "DESCRIPTION\n"
    "Core War is a programming game where players write small, "
    "self-replicating programs (called warriors) that compete for control "
    "of a virtual computer's memory (the Core). The goal is to disable "
    "opponents' programs while ensuring your own survives\n"
    "The bonus is comprised of two parts: the menu (made using raylib) "
    "and the game (made in ncurses). The ncurses control are available by "
    "pressing 'h' during its execution.\n\n"
    ""
    "Have fun!\n"
    "Axistorm & Arkcadia <3\n";

void display_usage(void)
{
    if (BONUS_MODE == 0)
        write(STDOUT_FILENO, usage_text, sizeof(usage_text));
    else
        write(STDOUT_FILENO, bonus_usage_text, sizeof(bonus_usage_text));
}
