cmake_minimum_required(VERSION 3.10.0)

project(mystd)

add_library(mystd STATIC
    my_stype/my_str_isalnum.c
    my_stype/my_str_isalpha.c
    my_stype/my_str_isblank.c
    my_stype/my_str_iscntrl.c
    my_stype/my_str_isdigit.c
    my_stype/my_str_isgraph.c
    my_stype/my_str_islower.c
    my_stype/my_str_isprint.c
    my_stype/my_str_ispunct.c
    my_stype/my_str_isspace.c
    my_stype/my_str_isupper.c
    my_stype/my_str_isxdigit.c
    my_stype/my_str_tolower.c
    my_stype/my_str_toupper.c
)

target_include_directories(mystd PRIVATE ../include)
