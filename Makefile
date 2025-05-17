NAME = corewar
LIB = libmystd.a

CC = clang
CFLAGS = $(pkg-config --libs --cflags raylib) \
         audio_player `sdl2-config --cflags --libs` -lSDL2_mixer
LDFLAGS = -Llibs -lmystd

CMAKE_DEBUG_FLAGS = -fsanitize=address -Weverything \
                    -Wno-unsafe-buffer-usage \
                    -Wno-pre-c23-compat -Wno-cast-qual -Wno-vla
CMAKE_BONUS_FLAG = -O3 -Wno-unused-result
CMAKE_TESTS_FLAGS = -lcriterion --coverage -lgcov

MAKEFLAGS += --no-print-directory

.PHONY: all
all: $(NAME)

$(NAME):
	@mkdir -p build
	@cd build && CC=$(CC) cmake -DCMAKE_BUILD_TYPE=Debug \
	        -DCMAKE_CXX_FLAGS="" \
	        -DCMAKE_C_FLAGS="" \
	        -DCMAKE_EXE_LINKER_FLAGS="" ..
	@cmake --build build --parallel 12
	@cp build/$(NAME) .

.PHONY: lib
lib:
	@mkdir -p build
	@cd build && CC=$(CC) cmake -DCMAKE_BUILD_TYPE=Debug ..
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

.PHONY: bonus
bonus:
	@mkdir -p build
	@cd build && CC=$(CC) cmake -DCMAKE_BUILD_TYPE=Bonus \
	        -DCMAKE_CXX_FLAGS="" \
	        -DCMAKE_C_FLAGS="$(CMAKE_BONUS_FLAG)" \
	        -DCMAKE_EXE_LINKER_FLAGS="" ..
	@cmake --build build --parallel 12
	@cp build/$(NAME) .

.PHONY: tests_run
tests_run: fclean
	@mkdir -p build
	@cd build && CC=$(CC) cmake -DCMAKE_BUILD_TYPE=Tests \
	        -DCMAKE_CXX_FLAGS="" \
	        -DCMAKE_C_FLAGS="$(CMAKE_TESTS_FLAGS)" \
	        -DCMAKE_EXE_LINKER_FLAGS="" ..
	@cmake --build build --parallel 12
	@cp build/$(NAME) .
	@./$(NAME) -j12

.PHONY: coverage
coverage:
	@$(MAKE) tests_run 2>&1 1>/dev/null
	@gcovr --sort uncovered-percent

.PHONY: clean
clean:
	@rm -rf build
	@rm -rf cmake-build-debug
	@rm -f *.gcno *.gcda *.gcov *.html *.css

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)
	@rm -f libs/$(LIB)

.PHONY: re
re: fclean all
