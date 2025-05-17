NAME = corewar
CC = clang
BUILD_DIR = build

.PHONY: all
all: release

.PHONY: release
release:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Release ..
	@cmake --build $(BUILD_DIR) --parallel 12
	@cp $(BUILD_DIR)/$(NAME) .

.PHONY: debug
debug:
	@mkdir -p $(BUILD_DIR)
	@cd $(BUILD_DIR) && cmake -DCMAKE_BUILD_TYPE=Debug ..
	@cmake --build $(BUILD_DIR) --parallel 12
	@cp $(BUILD_DIR)/$(NAME) .

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)

.PHONY: fclean
fclean: clean
	@rm -f $(NAME)

.PHONY: re
re: fclean all
