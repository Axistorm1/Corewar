#ifndef MY_SIZE_T_H_
    #define MY_SIZE_T_H_

typedef unsigned long my_size_t;

#endif /* MY_SIZE_T_H_ */

#ifndef MY_STYPE_H_
    #define MY_STYPE_H_

[[gnu::nonnull(1)]]
int my_str_isalnum(const char *str);
[[gnu::nonnull(1)]]
int my_str_isalpha(const char *str);
[[gnu::nonnull(1)]]
int my_str_isblank(const char *str);
[[gnu::nonnull(1)]]
int my_str_iscntrl(const char *str);
[[gnu::nonnull(1)]]
int my_str_isdigit(const char *str);
[[gnu::nonnull(1)]]
int my_str_isgraph(const char *str);
[[gnu::nonnull(1)]]
int my_str_islower(const char *str);
[[gnu::nonnull(1)]]
int my_str_isprint(const char *str);
[[gnu::nonnull(1)]]
int my_str_ispunct(const char *str);
[[gnu::nonnull(1)]]
int my_str_isspace(const char *str);
[[gnu::nonnull(1)]]
int my_str_isupper(const char *str);
[[gnu::nonnull(1)]]
int my_str_isxdigit(const char *str);
[[gnu::nonnull(1)]]
char *my_str_tolower(char *str);
[[gnu::nonnull(1)]]
char *my_str_toupper(char *str);

#endif /* MY_STYPE_H_ */
