##
## EPITECH PROJECT, 2024
## my_ctype
## File description:
## Makefile to make files
##

SRC		=	my_isalnum.c	\
			my_isalpha.c	\
			my_isblank.c	\
			my_iscntrl.c	\
			my_isdigit.c	\
			my_isgraph.c	\
			my_islower.c	\
			my_isprint.c	\
			my_ispunct.c	\
			my_isspace.c	\
			my_isupper.c	\
			my_isxdigit.c	\
			my_tolower.c	\
			my_toupper.c	\

OBJ		=	$(SRC:.c=.o)

NAME	=	my_ctype.a

CFLAGS += -Weverything -std=c2x -Wno-missing-variable-declarations
CFLAGS += -Wno-unsafe-buffer-usage -Wno-pre-c2x-compat -Wno-vla

CC = clang

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all:	$(SRC) $(NAME)

build: $(OBJ)

$(NAME): build
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:	clean
	@rm -f $(NAME)

re:	fclean $(NAME)

.PHONY:	$(NAME) all clean fclean re
