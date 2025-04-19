/*
** EPITECH PROJECT, 2024
** my_ctype
** File description:
** Header for my_ctype
*/

#ifndef MY_SIZE_T_H_
    #define MY_SIZE_T_H_

typedef unsigned long my_size_t;

#endif /* MY_SIZE_T_H_ */

#ifndef MY_STYPE_H_
    #define MY_STYPE_H_

int my_str_isalnum(char *str)
__attribute__((nonnull(1)));
int my_str_isalpha(char *str)
__attribute__((nonnull(1)));
int my_str_isblank(char *str)
__attribute__((nonnull(1)));
int my_str_iscntrl(char *str)
__attribute__((nonnull(1)));
int my_str_isdigit(char *str)
__attribute__((nonnull(1)));
int my_str_isgraph(char *str)
__attribute__((nonnull(1)));
int my_str_islower(char *str)
__attribute__((nonnull(1)));
int my_str_isprint(char *str)
__attribute__((nonnull(1)));
int my_str_ispunct(char *str)
__attribute__((nonnull(1)));
int my_str_isspace(char *str)
__attribute__((nonnull(1)));
int my_str_isupper(char *str)
__attribute__((nonnull(1)));
int my_str_isxdigit(char *str)
__attribute__((nonnull(1)));
char *my_str_tolower(char *str)
__attribute__((nonnull(1)));
char *my_str_toupper(char *str)
__attribute__((nonnull(1)));

#endif /* MY_STYPE_H_ */
