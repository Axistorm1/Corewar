##
## EPITECH PROJECT, 2024
## My libs
## File description:
## Makefile to make files
##

LIBS_DIR	= 	my_ctype	\
				my_stdlib	\
				my_string	\

LIBS_HEADERS	= 	my_ctype/my_ctype.h \
					my_stdlib/my_stdlib.h \
					my_string/my_string.h \

GLOBAL_LIB	=	my_libs.a

.PHONY: all
all: $(GLOBAL_LIB)

.PHONY: build
build:
	@for dir in $(LIBS_DIR); do \
	    echo "\033[31mBuilding $$dir \033[0m"; \
		$(MAKE) -s -C $$dir build; \
	done

.PHONY: $(GLOBAL_LIB)
$(GLOBAL_LIB):	build
	@for dir in $(LIBS_DIR); do \
		mv $$dir/*.o .; \
	done
	@rm -f $(GLOBAL_LIB)
	@ar rc $(GLOBAL_LIB) *.o
	@rm -f *.o

.PHONY: include
include: $(GLOBAL_LIB)
	rm -rf include
	mkdir include
	@for header in $(LIBS_HEADERS); do \
		cp $$header include/; \
	done

.PHONY: clean
clean:
	@rm -f *.o

.PHONY: fclean
fclean: clean
	@rm -f $(GLOBAL_LIB)
	@rm -rf include/

.PHONY: re
re: fclean $(GLOBAL_LIB)
