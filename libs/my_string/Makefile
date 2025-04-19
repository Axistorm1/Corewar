##
## EPITECH PROJECT, 2024
## my_string
## File description:
## Makefile to make files
##

SRC		=	my_c_to_bin.c	\
			my_memccpy.c	\
			my_memchr.c	\
			my_memcmp.c	\
			my_memcpy.c	\
			my_memmove.c	\
			my_memrcpy.c	\
			my_memset.c	\
			my_strcat.c	\
			my_strchr.c	\
			my_strcmp.c	\
			my_strcnb.c	\
			my_strcpy.c	\
			my_strcspn.c	\
			my_strdup.c	\
			my_strndup.c	\
			my_strlen.c	\
			my_strncat.c	\
			my_strncmp.c	\
			my_strncpy.c	\
			my_strpbrk.c	\
			my_strrchr.c	\
			my_strrev.c	\
			my_strspn.c	\
			my_strstr.c	\
			my_str_to_bin.c	\
			my_strtok.c	\
			my_str_to_word_array.c	\
			str_to_word_array.c	\
			my_strcasecmp.c	\
			str_array_len.c	\
			str_toupper.c	\
			str_tolower.c	\
			my_stradd.c	\

OBJ		=	$(SRC:.c=.o)

NAME	=	my_string.a

CFLAGS += -Weverything -std=c2x
CFLAGS += -Wno-unsafe-buffer-usage -Wno-pre-c2x-compat -Wno-vla -Wno-cast-qual

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
