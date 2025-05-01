/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Checks if a character is a control character
*/

#include "my_ctype.h"
#include "private.h"

int my_iscntrl(char c)
{
    if (c >= CNTRL1_MIN && c <= CNTRL1_MAX)
        return 1;
    if (c == TAB || c == DEL)
        return 1;
    if (c >= CNTRL2_MIN && c <= CNTRL2_MAX)
        return 1;
    if (c >= CNTRL3_MIN && c <= CNTRL3_MAX)
        return 1;
    return 0;
}
