CC          := cc
CFLAGS      := -Wall -Wextra -Werror

# `make BUFFER_SIZE=1`
BUFFER_SIZE ?= 42
CFLAGS      += -D BUFFER_SIZE=$(BUFFER_SIZE)

GNL_BIN      := gnl_main
GNL_BONUSBIN := gnl_main_bonus

GNL_SRC       := main.c get_next_line.c get_next_line_utils.c
GNL_INC       := -I .

GNL_BONUS_SRC := main_bonus.c get_next_line_bonus.c get_next_line_utils_bonus.c
GNL_BONUS_INC := -I .

# Default file to run; can override: `make run FILE=tests/single_line.txt`
FILE ?= tests/file1.txt

.PHONY: all gnl bonus run run-bonus clean fclean re

all: gnl bonus

# Build regular main
$(GNL_BIN): $(GNL_SRC)
	@echo "🔧 Building $(GNL_BIN) (BUFFER_SIZE=$(BUFFER_SIZE))"
	@$(CC) $(CFLAGS) $(GNL_SRC) $(GNL_INC) -o $(GNL_BIN)

gnl: $(GNL_BIN)

# Build bonus main
$(GNL_BONUSBIN): $(GNL_BONUS_SRC)
	@echo "🔧 Building $(GNL_BONUSBIN) (BUFFER_SIZE=$(BUFFER_SIZE))"
	@$(CC) $(CFLAGS) $(GNL_BONUS_SRC) $(GNL_BONUS_INC) -o $(GNL_BONUSBIN)

bonus: $(GNL_BONUSBIN)

# Run helpers
run: gnl
	@echo "▶️  Running: ./$(GNL_BIN) $(FILE)"
	@./$(GNL_BIN) $(FILE)

run-bonus: bonus
	@echo "▶️  Running: ./$(GNL_BONUSBIN) $(FILE)"
	@./$(GNL_BONUSBIN) $(FILE)

clean:
	@rm -f $(GNL_BIN) $(GNL_BONUSBIN)
	@echo "🧹 Removed binaries."

fclean: clean

re: fclean all
