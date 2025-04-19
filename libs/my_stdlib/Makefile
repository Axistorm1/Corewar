##
## EPITECH PROJECT, 2024
## My stdlib
## File description:
## Makefile to make files
##

SRC		=	my_abs.c	\
			my_atof.c	\
			my_atoi.c	\
			my_atol.c	\
			my_ltoa.c	\
			my_itoa.c	\
			my_bytes_rev.c	\
			my_calloc.c	\
			my_div.c	\
			my_free.c	\
			my_labs.c	\
			my_ldiv.c	\
			my_malloc.c	\
			my_realloc.c	\
			my_reallocarray.c	\
			my_strtod.c	\
			my_strtol.c	\
			my_getenv.c	\
			get_chunk_size.c	\

OBJ		=	$(SRC:.c=.o)

NAME    =   my_stdlib.a

CFLAGS += -Weverything -std=c2x
CFLAGS += -Wno-unsafe-buffer-usage -Wno-pre-c2x-compat -Wno-vla -Wno-cast-qual

CC = clang

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(SRC) $(NAME)

build: $(OBJ)

$(NAME): build
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re:	fclean all
