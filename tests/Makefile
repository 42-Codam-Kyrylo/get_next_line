# **************************************************************************** #
#                        GET_NEXT_LINE TEST MAKEFILE                           #
# **************************************************************************** #

CC          = gcc
CFLAGS      = -Wall -Wextra -Werror -D BUFFER_SIZE=42

# Пути
ROOT_DIR    = ..

# Определение ОС и путей к Criterion
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
    # macOS (Homebrew)
    BREW_PREFIX = $(shell brew --prefix)
    CRIT_INC    = -I $(BREW_PREFIX)/include
    CRIT_LIB    = -L $(BREW_PREFIX)/lib -lcriterion
    LD_PATH     = DYLD_LIBRARY_PATH=$(BREW_PREFIX)/lib
else
    # Linux
    CRIT_DIR    = $(HOME)/criterion-2.4.3-linux-x86_64/criterion-2.4.3
    CRIT_INC    = -I $(CRIT_DIR)/include
    CRIT_LIB    = -L $(CRIT_DIR)/lib -lcriterion
    LD_PATH     = LD_LIBRARY_PATH=$(CRIT_DIR)/lib
endif

# Файлы
TEST_SRC    = $(wildcard *.c)
GNL_SRC     = $(ROOT_DIR)/get_next_line.c $(ROOT_DIR)/get_next_line_utils.c
TEST_BIN    = test_gnl

# Test options
VERBOSE     ?= 
FILE        ?= 

COMPILE_ALL  = $(CC) $(CFLAGS) $(TEST_SRC) $(GNL_SRC) -I $(ROOT_DIR) $(CRIT_INC) $(CRIT_LIB) -o $(TEST_BIN)
COMPILE_FILE = $(CC) $(CFLAGS) $(FILE) $(GNL_SRC) -I $(ROOT_DIR) $(CRIT_INC) $(CRIT_LIB) -o $(TEST_BIN)
RUN_TESTS    = $(LD_PATH) ./$(TEST_BIN) $(VERBOSE)

# **************************************************************************** #
#                                   TARGETS                                    #
# **************************************************************************** #

all: test

test:
	@echo "🔧 Building and running tests..."
ifeq ($(FILE),)
	@$(COMPILE_ALL)
	@$(RUN_TESTS)
else
	@$(COMPILE_FILE)
	@$(RUN_TESTS)
endif

show: VERBOSE=--verbose
show: test

test-list:
	@echo "📋 Listing available tests..."
	@$(COMPILE_ALL)
	@$(LD_PATH) ./$(TEST_BIN) --list

clean:
	@rm -f $(TEST_BIN)
	@echo "🧹 Removed test binary."

fclean: clean

.PHONY: all test clean fclean show test-list