/*
** EPITECH PROJECT, 2025
** B-CPE-200-TLS-2-1-amazed-romeo.louvel
** File description:
** tests_lib_strings
*/

#include <assert.h>
#include <criterion/criterion.h>
#include <criterion/internal/assert.h>
#include "my_string.h"
#include "my_stdlib.h"
#include "my_ctype.h"
#include "my_string.h"
#include "my_stdlib.h"
#include "my_stype.h"

Test(my_string, my_strlen) {
    const char *str = "hello";
    size_t len = my_strlen(str);
    cr_assert_eq(len, 5, "Expected length to be 5, but got %zu", len);
}

Test(my_string, my_strcmp) {
    const char *str1 = "hello";
    const char *str2 = "hello";
    const char *str3 = "world";

    cr_assert_eq(my_strcmp(str1, str2), 0, "Expected strings to be equal");
    cr_assert_neq(my_strcmp(str1, str3), 0, "Expected strings to be different");
}

Test(my_string, my_strcpy) {
    char dest[6];
    const char *src = "hello";

    my_strcpy(dest, src);
    cr_assert_str_eq(dest, src, "Expected copied string to be '%s', but got '%s'", src, dest);
}

Test(my_stdlib, my_atoi) {
    cr_assert_eq(my_atoi("123"), 123, "Expected '123' to convert to 123");
    cr_assert_eq(my_atoi("-456"), -456, "Expected '-456' to convert to -456");
}

Test(my_stdlib, my_atol) {
    cr_assert_eq(my_atol("123"), 123, "Expected '123' to convert to 123");
    cr_assert_eq(my_atol("-456"), -456, "Expected '-456' to convert to -456");
}

Test(my_stdlib, my_atof) {
    cr_assert_eq(my_atof("123.673"), 123.673, "Expected '123.673' to convert to 123.673");
    cr_assert_eq(my_atof("-456.673"), -456.673, "Expected '-456.673' to convert to -456.673");
}

Test(my_ctype, my_isdigit) {
    cr_assert(my_isdigit('5'), "Expected '5' to be a digit");
    cr_assert_not(my_isdigit('a'), "Expected 'a' not to be a digit");
}

Test(my_string, my_strcat) {
    char dest[11] = "hello";
    const char *src = " world";

    my_strcat(dest, src);
    cr_assert_str_eq(dest, "hello world", "Expected concatenated string to be 'hello world', but got '%s'", dest);
}

Test(my_string, my_strncpy) {
    char dest[6];
    const char *src = "hello";

    my_strncpy(dest, src, 3);
    dest[3] = '\0';
    cr_assert_str_eq(dest, "hel", "Expected copied string to be 'hel', but got '%s'", dest);
}

Test(my_stdlib, my_itoa) {
    char buffer[12];

    my_itoa(123, buffer, 10);
    cr_assert_str_eq(buffer, "123", "Expected integer 123 to convert to string '123', but got '%s'", buffer);

    my_itoa(-456, buffer, 10);
    cr_assert_str_eq(buffer, "-456", "Expected integer -456 to convert to string '-456', but got '%s'", buffer);
}

Test(my_ctype, my_tolower) {
    cr_assert_eq(my_tolower('A'), 'a', "Expected 'A' to convert to 'a'");
    cr_assert_eq(my_tolower('a'), 'a', "Expected 'a' to remain 'a'");
    cr_assert_eq(my_tolower('1'), '1', "Expected '1' to remain '1'");
}

Test(my_ctype, my_toupper) {
    cr_assert_eq(my_toupper('a'), 'A', "Expected 'a' to convert to 'A'");
    cr_assert_eq(my_toupper('A'), 'A', "Expected 'A' to remain 'A'");
    cr_assert_eq(my_toupper('1'), '1', "Expected '1' to remain '1'");
}

Test(my_string, my_strchr) {
    const char *str = "hello";
    char *result = my_strchr(str, 'e');

    cr_assert_not_null(result, "Expected to find 'e' in '%s'", str);
    cr_assert_eq(*result, 'e', "Expected to find 'e', but got '%c'", *result);
}

Test(my_string, my_strstr) {
    const char *haystack = "hello world";
    const char *needle = "world";
    char *result = my_strstr(haystack, needle);

    cr_assert_not_null(result, "Expected to find '%s' in '%s'", needle, haystack);
    cr_assert_str_eq(result, "world", "Expected to find '%s', but got '%s'", needle, result);
}

Test(my_string, my_strncat) {
    char dest[11] = "hello";
    const char *src = " world";

    my_strncat(dest, src, 3);
    cr_assert_str_eq(dest, "hello wo", "Expected concatenated string to be 'hello wo', but got '%s'", dest);
}

Test(my_string, my_strrchr) {
    const char *str = "hello world";
    char *result = my_strrchr(str, 'o');

    cr_assert_not_null(result, "Expected to find 'o' in '%s'", str);
    cr_assert_eq(*result, 'o', "Expected to find 'o', but got '%c'", *result);
}

Test(my_string, my_strchr_not_found) {
    const char *str = "hello";
    char *result = my_strchr(str, 'z');

    cr_assert_null(result, "Expected to not find 'z' in '%s'", str);
}

Test(my_string, my_strstr_not_found) {
    const char *haystack = "hello world";
    const char *needle = "foo";
    char *result = my_strstr(haystack, needle);

    cr_assert_null(result, "Expected to not find '%s' in '%s'", needle, haystack);
}

Test(my_string, my_strncat_empty) {
    char dest[6] = "hello";
    const char *src = "";

    my_strncat(dest, src, 3);
    cr_assert_str_eq(dest, "hello", "Expected destination to remain 'hello', but got '%s'", dest);
}

Test(my_string, my_strncpy_empty) {
    char dest[6];
    const char *src = "";

    my_strncpy(dest, src, 3);
    dest[0] = '\0';
    cr_assert_str_eq(dest, "", "Expected destination to be empty, but got '%s'", dest);
}

Test(my_string, my_strrchr_not_found) {
    const char *str = "hello world";
    char *result = my_strrchr(str, 'z');

    cr_assert_null(result, "Expected to not find 'z' in '%s'", str);
}

Test(my_string, my_strcmp_empty) {
    const char *str1 = "";
    const char *str2 = "";

    cr_assert_eq(my_strcmp(str1, str2), 0, "Expected empty strings to be equal");
}

Test(my_string, my_strcat_empty) {
    char dest[6] = "hello";
    const char *src = "";

    my_strcat(dest, src);
    cr_assert_str_eq(dest, "hello", "Expected destination to remain 'hello', but got '%s'", dest);
}

Test(my_string, my_strcpy_empty) {
    char dest[6];
    const char *src = "";

    my_strcpy(dest, src);
    cr_assert_str_eq(dest, "", "Expected destination to be empty, but got '%s'", dest);
}

Test(my_string, my_strrchr_empty) {
    const char *str = "";
    char *result = my_strrchr(str, 'z');

    cr_assert_null(result, "Expected to not find 'z' in empty string");
}

Test(my_string, my_strcat_case_insensitive) {
    char dest[11] = "hello";
    const char *src = " WORLD";

    my_strcat(dest, src);
    cr_assert_str_eq(dest, "hello WORLD", "Expected concatenated string to be 'hello WORLD', but got '%s'", dest);
}

Test(my_string, my_strcpy_case_insensitive) {
    char dest[11];
    const char *src = "HELLO";

    my_strcpy(dest, src);
    cr_assert_str_eq(dest, "HELLO", "Expected copied string to be 'HELLO', but got '%s'", dest);
}

Test(my_string, my_strncpy_case_insensitive) {
    char dest[11];
    const char *src = "HELLO WORLD";

    my_strncpy(dest, src, 5);
    dest[5] = '\0';
    cr_assert_str_eq(dest, "HELLO", "Expected copied string to be 'HELLO', but got '%s'", dest);
}

Test(my_string, my_strncat_case_insensitive_empty) {
    char dest[6] = "hello";
    const char *src = "";

    my_strncat(dest, src, 3);
    cr_assert_str_eq(dest, "hello", "Expected destination to remain 'hello', but got '%s'", dest);
}

Test(my_string, my_strncpy_case_insensitive_empty) {
    char dest[6];
    const char *src = "";

    my_strncpy(dest, src, 3);
    dest[0] = '\0';
    cr_assert_str_eq(dest, "", "Expected destination to be empty, but got '%s'", dest);
}

Test(my_string, my_strrchr_case_insensitive) {
    const char *str = "hello world";
    char *result = my_strrchr(str, 'o');

    cr_assert_eq(result, strrchr(str, 'o'), "Expected to find 'o' in '%s'", str);
    cr_assert_eq(*result, 'o', "Expected to find 'o', but got '%c'", *result);
}

Test(my_string, my_strrchr_case_insensitive_not_found) {
    const char *str = "hello world";
    char *result = my_strrchr(str, 'Z');

    cr_assert_null(result, "Expected to not find 'Z' in '%s'", str);
}

Test(my_string, my_strcmp_case_insensitive) {
    const char *str1 = "hello";
    const char *str2 = "HELLO";

    cr_assert_eq(my_strcmp(str1, str2), strcmp(str1, str2), "Expected case-insensitive comparison to be equal");
}

Test(my_string, my_strcmp_case_insensitive_different) {
    const char *str1 = "hello";
    const char *str2 = "world";

    cr_assert_neq(my_strcmp(str1, str2), 0, "Expected case-insensitive comparison to be different");
}

Test(my_string, my_strcat_case_insensitive_empty) {
    char dest[6] = "hello";
    const char *src = "";

    my_strcat(dest, src);
    cr_assert_str_eq(dest, "hello", "Expected destination to remain 'hello', but got '%s'", dest);
}

Test(my_string, my_strcpy_case_insensitive_empty) {
    char dest[6];
    const char *src = "";

    my_strcpy(dest, src);
    cr_assert_str_eq(dest, "", "Expected destination to be empty, but got '%s'", dest);
}

Test(my_ctype, my_isalnum) {
    cr_assert(my_isalnum('A'), "Expected 'A' to be alphanumeric");
    cr_assert(my_isalnum('z'), "Expected 'z' to be alphanumeric");
    cr_assert(my_isalnum('5'), "Expected '5' to be alphanumeric");
    cr_assert_not(my_isalnum('@'), "Expected '@' not to be alphanumeric");
    cr_assert_not(my_isalnum(' '), "Expected ' ' not to be alphanumeric");
}

Test(my_ctype, my_isalpha) {
    cr_assert(my_isalpha('A'), "Expected 'A' to be alphabetic");
    cr_assert(my_isalpha('z'), "Expected 'z' to be alphabetic");
    cr_assert_not(my_isalpha('5'), "Expected '5' not to be alphabetic");
    cr_assert_not(my_isalpha('@'), "Expected '@' not to be alphabetic");
}

Test(my_ctype, my_isblank) {
    cr_assert(my_isblank(' '), "Expected ' ' to be blank");
    cr_assert(my_isblank('\t'), "Expected '\\t' to be blank");
    cr_assert_not(my_isblank('A'), "Expected 'A' not to be blank");
}

Test(my_ctype, my_iscntrl) {
    cr_assert(my_iscntrl('\n'), "Expected '\\n' to be a control character");
    cr_assert(my_iscntrl('\0'), "Expected '\\0' to be a control character");
    cr_assert_not(my_iscntrl('A'), "Expected 'A' not to be a control character");
}

Test(my_ctype, my_isgraph) {
    cr_assert(my_isgraph('A'), "Expected 'A' to be a graphical character");
    cr_assert(my_isgraph('!'), "Expected '!' to be a graphical character");
    cr_assert_not(my_isgraph(' '), "Expected ' ' not to be a graphical character");
}

Test(my_ctype, my_isprint) {
    cr_assert(my_isprint('A'), "Expected 'A' to be printable");
    cr_assert(my_isprint(' '), "Expected ' ' to be printable");
    cr_assert_not(my_isprint('\n'), "Expected '\\n' not to be printable");
}

Test(my_ctype, my_ispunct) {
    cr_assert(my_ispunct('!'), "Expected '!' to be a punctuation character");
    cr_assert(my_ispunct(','), "Expected ',' to be a punctuation character");
    cr_assert_not(my_ispunct('A'), "Expected 'A' not to be a punctuation character");
    cr_assert_not(my_ispunct(' '), "Expected ' ' not to be a punctuation character");
}

Test(my_ctype, my_isxdigit) {
    cr_assert(my_isxdigit('A'), "Expected 'A' to be a hexadecimal digit");
    cr_assert(my_isxdigit('f'), "Expected 'f' to be a hexadecimal digit");
    cr_assert(my_isxdigit('5'), "Expected '5' to be a hexadecimal digit");
    cr_assert_not(my_isxdigit('G'), "Expected 'G' not to be a hexadecimal digit");
    cr_assert_not(my_isxdigit('@'), "Expected '@' not to be a hexadecimal digit");
}

Test(my_stype, my_str_isalnum) {
    cr_assert(my_str_isalnum("Hello123"), "Expected 'Hello123' to be alphanumeric");
    cr_assert_not(my_str_isalnum("Hello!"), "Expected 'Hello!' not to be alphanumeric");
    cr_assert_not(my_str_isalnum(""), "Expected an empty string not to be alphanumeric");
}

Test(my_stype, my_str_isalpha) {
    cr_assert(my_str_isalpha("Hello"), "Expected 'Hello' to be alphabetic");
    cr_assert_not(my_str_isalpha("Hello123"), "Expected 'Hello123' not to be alphabetic");
    cr_assert_not(my_str_isalpha(""), "Expected an empty string not to be alphabetic");
}

Test(my_stype, my_str_isblank) {
    cr_assert(my_str_isblank("   "), "Expected '   ' to be blank");
    cr_assert_not(my_str_isblank("Hello"), "Expected 'Hello' not to be blank");
    cr_assert_not(my_str_isblank(""), "Expected an empty string not to be blank");
}

Test(my_stype, my_str_iscntrl) {
    cr_assert(my_str_iscntrl("\n\t"), "Expected '\\n\\t' to be control characters");
    cr_assert_not(my_str_iscntrl("Hello"), "Expected 'Hello' not to be control characters");
    cr_assert_not(my_str_iscntrl(""), "Expected an empty string not to be control characters");
}

Test(my_stype, my_str_isdigit) {
    cr_assert(my_str_isdigit("12345"), "Expected '12345' to be digits");
    cr_assert_not(my_str_isdigit("123a"), "Expected '123a' not to be digits");
    cr_assert_not(my_str_isdigit(""), "Expected an empty string not to be digits");
}

Test(my_stype, my_str_isgraph) {
    cr_assert(my_str_isgraph("Hello!"), "Expected 'Hello!' to be graphical");
    cr_assert_not(my_str_isgraph(" "), "Expected ' ' not to be graphical");
    cr_assert_not(my_str_isgraph(""), "Expected an empty string not to be graphical");
}

Test(my_stype, my_str_islower) {
    cr_assert(my_str_islower("hello"), "Expected 'hello' to be lowercase");
    cr_assert_not(my_str_islower("Hello"), "Expected 'Hello' not to be lowercase");
    cr_assert_not(my_str_islower(""), "Expected an empty string not to be lowercase");
}

Test(my_stype, my_str_isprint) {
    cr_assert(my_str_isprint("Hello "), "Expected 'Hello ' to be printable");
    cr_assert_not(my_str_isprint("\n"), "Expected '\\n' not to be printable");
    cr_assert_not(my_str_isprint(""), "Expected an empty string not to be printable");
}

Test(my_stype, my_str_ispunct) {
    cr_assert(my_str_ispunct("!@#"), "Expected '!@#' to be punctuation");
    cr_assert_not(my_str_ispunct("Hello"), "Expected 'Hello' not to be punctuation");
    cr_assert_not(my_str_ispunct(""), "Expected an empty string not to be punctuation");
}

Test(my_stype, my_str_isspace) {
    cr_assert(my_str_isspace("   "), "Expected '   ' to be whitespace");
    cr_assert_not(my_str_isspace("Hello"), "Expected 'Hello' not to be whitespace");
    cr_assert_not(my_str_isspace(""), "Expected an empty string not to be whitespace");
}

Test(my_stype, my_str_isupper) {
    cr_assert(my_str_isupper("HELLO"), "Expected 'HELLO' to be uppercase");
    cr_assert_not(my_str_isupper("Hello"), "Expected 'Hello' not to be uppercase");
    cr_assert_not(my_str_isupper(""), "Expected an empty string not to be uppercase");
}

Test(my_stype, my_str_isxdigit) {
    cr_assert(my_str_isxdigit("123ABC"), "Expected '123ABC' to be hexadecimal digits");
    cr_assert_not(my_str_isxdigit("123G"), "Expected '123G' not to be hexadecimal digits");
    cr_assert_not(my_str_isxdigit(""), "Expected an empty string not to be hexadecimal digits");
}

Test(my_stype, my_str_tolower) {
    char str[] = "HELLO";
    my_str_tolower(str);
    cr_assert_str_eq(str, "hello", "Expected 'HELLO' to convert to 'hello'");
}

Test(my_stype, my_str_toupper) {
    char str[] = "hello";
    my_str_toupper(str);
    cr_assert_str_eq(str, "HELLO", "Expected 'hello' to convert to 'HELLO'");
}

Test(my_string, str_array_len) {
    char *array[] = {"hello", "world", "test", NULL};
    size_t len = str_array_len(array);

    cr_assert_eq(len, 3, "Expected array length to be 3, but got %zu", len);
}

Test(my_string, str_tolower) {
    char str[] = "HELLO WORLD";
    str_tolower(str);

    cr_assert_str_eq(str, "hello world", "Expected 'HELLO WORLD' to convert to 'hello world', but got '%s'", str);

    char empty_str[] = "";
    str_tolower(empty_str);
    cr_assert_str_eq(empty_str, "", "Expected empty string to remain unchanged, but got '%s'", empty_str);
}

Test(my_string, str_toupper) {
    char str[] = "hello world";
    str_toupper(str);

    cr_assert_str_eq(str, "HELLO WORLD", "Expected 'hello world' to convert to 'HELLO WORLD', but got '%s'", str);

    char empty_str[] = "";
    str_toupper(empty_str);
    cr_assert_str_eq(empty_str, "", "Expected empty string to remain unchanged, but got '%s'", empty_str);
}

Test(my_stdlib, my_abs) {
    cr_assert_eq(my_abs(5), abs(5), "Expected absolute value of 5 to be 5");
    cr_assert_eq(my_abs(-5), abs(-5), "Expected absolute value of -5 to be 5");
    cr_assert_eq(my_abs(0), abs(0), "Expected absolute value of 0 to be 0");
}

Test(my_string, my_strspn_basic) {
    const char *str = "abcde12345";
    const char *accept = "abcde";

    size_t result = my_strspn(str, accept);
    cr_assert_eq(result, strspn(str, accept), "Expected initial segment length to be 5, but got %zu", result);
}

Test(my_string, my_strspn_no_match) {
    const char *str = "12345abcde";
    const char *accept = "abcde";

    size_t result = my_strspn(str, accept);
    cr_assert_eq(result, strspn(str, accept), "Expected initial segment length to be 0, but got %zu", result);
}

Test(my_string, my_strspn_empty_string) {
    const char *str = "";
    const char *accept = "abcde";

    size_t result = my_strspn(str, accept);
    cr_assert_eq(result, 0, "Expected initial segment length to be 0 for an empty string, but got %zu", result);
}

Test(my_string, my_strspn_repeated_chars) {
    const char *str = "abcabcabc";
    const char *accept = "abc";

    size_t result = my_strspn(str, accept);
    cr_assert_eq(result, 9, "Expected initial segment length to be 9, but got %zu", result);
}

Test(my_string, my_strndup_partial) {
    const char *src = "hello world";

    char *dup = my_strndup(src, 5);
    cr_assert_str_eq(dup, "hello", "Expected duplicated string to be 'hello', but got '%s'", dup);
    free(dup);
}

Test(my_string, my_strndup_full) {
    const char *src = "hello world";

    char *dup = my_strndup(src, 20);
    cr_assert_str_eq(dup, "hello world", "Expected duplicated string to be 'hello world', but got '%s'", dup);
    free(dup);
}

Test(my_string, my_strndup_empty_length) {
    const char *src = "hello world";

    char *dup = my_strndup(src, 0);
    cr_assert_str_eq(dup, "", "Expected duplicated string to be empty, but got '%s'", dup);
    free(dup);
}

Test(my_string, my_strndup_empty_source) {
    const char *src = "";

    char *dup = my_strndup(src, 5);
    cr_assert_str_eq(dup, "", "Expected duplicated string to be empty, but got '%s'", dup);
    free(dup);
}

Test(my_iscntrl, my_iscntrl_last_condition) {
    const char src = 0x1F;
    bool value = my_iscntrl(src);
    cr_assert_eq(value, true);
}

Test(my_ispunct, my_ispunct_last_conditions) {
    char src = 0x5B;
    bool value = my_ispunct(src);
    cr_assert_eq(value, true);

    src = 0x7B;
    value = my_ispunct(src);
    cr_assert_eq(value, true);
}

Test(my_reallocarray, my_reallocarray)
{
    char **ptr = my_malloc(12 * sizeof(char *));
    ptr = my_reallocarray(ptr, 15, sizeof(char *));
}

Test(my_strpbrk, my_strpbrk)
{
    char ptr[] = "Hello";
    my_strpbrk(ptr, "a");
}
