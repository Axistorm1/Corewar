##
## EPITECH PROJECT, 2025
## Corewar
## File description:
## Makefile to make files
##

NAME	=	corewar
LIB		=	libmystd.a

CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS = -Llibs -lmystd

MAKEFLAGS += --no-print-directory

CMAKE_DEBUG_FLAGS := -fsanitize=address -Weverything	\
	-Wno-unsafe-buffer-usage	\
	-Wno-pre-c23-compat -Wno-cast-qual -Wno-vla	\

.PHONY: all
all: $(NAME)

.PHONY: $(NAME)
$(NAME):
	@mkdir -p build
	@cd build && CC=gcc cmake -DCMAKE_BUILD_TYPE=Debug ..
	@cmake --build build --parallel 12
	@cp build/$(NAME) .

.PHONY: lib
lib:
	@mkdir -p build
	cd build && CC=gcc cmake -DCMAKE_BUILD_TYPE=Debug ..
	@cmake --build build --target mystd --parallel 12
	@cp build/libs/$(LIB) libs/

.PHONY: debug
debug:
	@mkdir -p build
	@cd build && CC=clang cmake -DCMAKE_BUILD_TYPE=Debug \
	        -DCMAKE_CXX_FLAGS="-fsanitize=address" \
			-DCMAKE_C_FLAGS="$(CMAKE_DEBUG_FLAGS)" \
 			-DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address" ..
	@cmake --build build --parallel 12
	@cp build/$(NAME) .

.PHONY: clean
clean:
	rm -rf build
	rm -rf cmake-build-debug
	rm -f *.gcno
	rm -f *.gcda
	rm -f *.gcov
	rm -f *.html
	rm -f *.css

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	rm -f libs/$(LIB)

.PHONY: re
re: fclean all
