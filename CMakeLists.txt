cmake_minimum_required(VERSION 3.10.0)

project(corewar C)

set(CMAKE_C_COMPILER clang)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES
    src/*.c
    src/arena/*.c
    src/arena/instructions/*.c
    src/graphic/*.c
    src/graphic/menu/*.c
    src/utils/*.c
    src/parsing/*.c)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
pkg_check_modules(RAYLIB REQUIRED raylib)

include_directories(include ${RAYLIB_INCLUDE_DIRS})

add_compile_definitions(BONUS_MODE=1)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-Weverything -Wall -Wextra -Wconversion -Wpedantic
        -fsanitize=address
        -Wno-unsafe-buffer-usage
        -Wno-pre-c23-compat -Wno-cast-qual -Wno-vla
        -Wunused-result)
    add_link_options(-fsanitize=address)
endif()

add_executable(corewar ${SOURCES})

target_link_libraries(corewar PRIVATE
    ncurses
    ${RAYLIB_LIBRARIES}
    ${SDL2_LIBRARIES}
    ${SDL2_MIXER_LIBRARIES}
    m pthread dl rt X11)
