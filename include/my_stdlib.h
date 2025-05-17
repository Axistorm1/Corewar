#ifndef MY_NULL_H_
    #define MY_NULL_H_

    #define MY_NULL ((void *)0)

#endif /* MY_NULL_H_ */

#ifndef MY_SIZE_T_H_
    #define MY_SIZE_T_H_

typedef unsigned long my_size_t;

#endif /* MY_SIZE_T_H_ */

#ifndef MY_WCHAR_T_H_
    #define MY_WCHAR_T_H_

typedef unsigned int my_wchar_t;

#endif /* MY_WCHAR_T_H_ */

#ifndef MY_STDLIB_H_
    #define  MY_STDLIB_H_

    // Macros
    #define MY_EXIT_FAILURE 84
    #define MY_EXIT_SUCCESS 0
    #define MY_RAND_MAX 2147483647
    #define ABS(x) (x > 0 ? x : -x)
    #define MIN(x, y) (x < y ? x : y)
    #define MAX(x, y) (x > y ? x : y)
    #define ROL_32(x, y) ((x << y) | (x >> (32 - y)))
    #define ROR_32(x, y) ((x >> y) | (x << (32 - y)))

// Functions
void *my_calloc(my_size_t nitems, my_size_t size);
void my_free(void *ptr);
void *my_malloc(my_size_t size);
void *my_realloc(void *ptr, my_size_t size, my_size_t old_size);
void *my_reallocarray(void *ptr, my_size_t nmemb, my_size_t size);
char *my_strdup(const char *str);
my_size_t str_array_len(char **array);
void free_garbage(void);

#endif /* MY_STDLIB_H_ */
