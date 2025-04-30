/*
** EPITECH PROJECT, 2025
** asm
** File description:
** transform little endian to big endian
*/

unsigned int swap_endian(
    unsigned int num)
{
    return ((num >> 24) & 0xFF) |
        ((num >> 8) & 0xFF00) |
        ((num << 8) & 0xFF0000) |
        ((num << 24) & 0xFF000000);
}
