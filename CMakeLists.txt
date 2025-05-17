cmake_minimum_required(VERSION 3.10.0)

project(corewar)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SOURCES
    src/*.c
    src/arena/*.c
    src/arena/instructions/*.c
    src/utils/*.c
    src/parsing/*.c)

if (${CMAKE_BUILD_TYPE} MATCHES "Tests")
    list(REMOVE_ITEM SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
    set(SOURCES ${SOURCES} tests/tests_parsing.c tests/tests_corewar.c)
endif()

if(${CMAKE_BUILD_TYPE} MATCHES "Bonus")
    add_compile_options(-Wall -Wextra -Wconversion -Wpedantic)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_MIXER REQUIRED SDL2_mixer)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(RAYLIB REQUIRED raylib)
    include_directories(${RAYLIB_INCLUDE_DIRS} bonus/include)
    link_directories(${RAYLIB_LIBRARY_DIRS})
    add_compile_definitions(BONUS_MODE=1)
    set(SOURCES ${SOURCES} bonus/bonus.c bonus/transcribe_dot_s.c bonus/parse_champion.c bonus/menu/menu.c bonus/audio.c)
    set(RAYLIB_LIBS ${RAYLIB_LIBRARIES} -lGL -lm -lpthread -ldl -lrt -lX11)
endif()

add_executable(corewar ${SOURCES})
target_include_directories(corewar PRIVATE include)

add_subdirectory(libs)

target_link_libraries(corewar PRIVATE mystd)
if(${CMAKE_BUILD_TYPE} MATCHES "Bonus")
    target_link_libraries(corewar PRIVATE mystd ncurses ${RAYLIB_LIBS} ${SDL2_LIBRARIES} ${SDL2_MIXER_LIBRARIES})
endif()

target_include_directories(corewar PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/libs")
set_property(TARGET corewar PROPERTY C_STANDARD 23)
