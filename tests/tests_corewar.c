#include <assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include "corewar.h"
#include "my_stdlib.h"
#include "my_stdlib.h"
#include "my_stype.h"

extern char **environ;

Test(run_corewar, run_corewar_usage) {
    const char *args[] = {"./corewar", "-h", NULL};
    run_corewar(2, args, environ);
}

Test(run_corewar, run_corewar_no_args) {
    const char *args[] = {"./corewar", NULL};
    run_corewar(1, args, environ);
}

Test(run_corewar, run_corewar_no_robot) {
    const char *args[] = {"./corewar", "-a", "12", NULL};
    run_corewar(3, args, environ);
}

Test(run_corewar, run_corewar_missing_file) {
    const char *args[] = {"./corewar", "the_game.cor", NULL};
    run_corewar(2, args, environ);
}

Test(run_corewar, run_corewar_one_champ) {
    const char *args[] = {"./corewar", "-n", "12", "bonus/champions/bill.cor", NULL};
    run_corewar(4, args, environ);
}

Test(run_corewar, run_corewar_two_champs) {
    const char *args[] = {"./corewar", "bonus/champions/abel.cor", "bonus/champions/bill.cor", NULL};
    run_corewar(3, args, environ);
}

Test(run_corewar, run_corewar_two_placed_two_non_placed_champs) {
    const char *args[] = {"./corewar", "bonus/champions/abel.cor", "bonus/champions/bill.cor", "-n", "1", "-a", "0", "bonus/champions/bill.cor", "-a", "4000", "bonus/champions/abel.cor", NULL};
    run_corewar(11, args, environ);
}

Test(run_corewar, run_corewar_two_placed_three_non_placed_champs) {
    const char *args[] = {"./corewar", "bonus/champions/abel.cor", "bonus/champions/bill.cor", "-n", "1", "-a", "0", "bonus/champions/bill.cor", "-a", "4000", "bonus/champions/Kappa.cor", "bonus/champions/42.cor", "bonus/champions/Asombra.cor", NULL};
    run_corewar(12, args, environ);
}

Test(run_corewar, run_corewar_two_placed_three_non_placed_champs_with_dump) {
    const char *args[] = {"./corewar", "-dump", "100", "bonus/champions/abel.cor", "bonus/champions/bill.cor", "-n", "1", "-a", "0", "bonus/champions/bill.cor", "-a", "4000", "bonus/champions/Kappa.cor", "bonus/champions/42.cor", "bonus/champions/Asombra.cor", NULL};
    run_corewar(14, args, environ);
}
