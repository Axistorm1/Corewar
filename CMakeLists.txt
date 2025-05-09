cmake_minimum_required(VERSION 3.10.0)

project(corewar)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -Wconversion -Wpedantic)

file(GLOB SOURCES
    src/*.c
    src/utils/*.c
    src/arena/*.c
    src/parsing/*.c)

if(${CMAKE_BUILD_TYPE} MATCHES "Bonus")
    add_compile_definitions(BONUS_MODE=1)
    set(SOURCES ${SOURCES} bonus/bonus.c)
endif()

add_executable(corewar ${SOURCES})

target_include_directories(corewar PRIVATE include)

add_subdirectory(libs)

target_link_libraries(corewar PRIVATE mystd)
if(${CMAKE_BUILD_TYPE} MATCHES "Bonus")
    target_link_libraries(corewar PRIVATE mystd ncurses m)
endif()

target_include_directories(corewar PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/libs")

set_property(TARGET corewar PROPERTY C_STANDARD 23)
