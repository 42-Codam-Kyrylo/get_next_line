# **************************************************************************** #
#                        GET_NEXT_LINE TEST MAKEFILE                           #
# **************************************************************************** #

CC          = gcc
# Default flags; BUFFER_SIZE can be overridden: `make test BUFFER_SIZE=42`
CFLAGS      = -Wall -Wextra -Werror

# BUFFER_SIZE control (default 1)
BUFFER_SIZE ?= 42
CFLAGS     += -D BUFFER_SIZE=$(BUFFER_SIZE)

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
TEST_SRC       = $(wildcard *.c)
GNL_SRC        = $(ROOT_DIR)/get_next_line.c $(ROOT_DIR)/get_next_line_utils.c
TEST_BIN       = test_gnl

# Bonus files
BONUS_TEST_SRC = $(wildcard bonus/*.c)
GNL_BONUS_SRC  = $(ROOT_DIR)/get_next_line_bonus.c $(ROOT_DIR)/get_next_line_utils_bonus.c
TEST_BONUS_BIN = test_gnl_bonus

# Test options
VERBOSE     ?= 
FILE        ?= 

# Valgrind configuration (override from CLI if desired):
#   make valgrind VG_OPTS="--leak-check=full --track-origins=yes" FILE=edge_cases.test.c
VALGRIND    ?= valgrind
VG_OPTS     ?= --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=1

COMPILE_ALL       = $(CC) $(CFLAGS) $(TEST_SRC) $(GNL_SRC) -I $(ROOT_DIR) $(CRIT_INC) $(CRIT_LIB) -o $(TEST_BIN)
COMPILE_FILE      = $(CC) $(CFLAGS) $(FILE) $(GNL_SRC) -I $(ROOT_DIR) $(CRIT_INC) $(CRIT_LIB) -o $(TEST_BIN)
RUN_TESTS         = $(LD_PATH) ./$(TEST_BIN) $(VERBOSE)

COMPILE_ALL_BONUS  = $(CC) $(CFLAGS) $(BONUS_TEST_SRC) $(GNL_BONUS_SRC) -I $(ROOT_DIR) $(CRIT_INC) $(CRIT_LIB) -o $(TEST_BONUS_BIN)
COMPILE_FILE_BONUS = $(CC) $(CFLAGS) $(FILE) $(GNL_BONUS_SRC) -I $(ROOT_DIR) $(CRIT_INC) $(CRIT_LIB) -o $(TEST_BONUS_BIN)
RUN_TESTS_BONUS    = $(LD_PATH) ./$(TEST_BONUS_BIN) $(VERBOSE)

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

# Bonus tests
bonus: test-bonus

test-bonus:
	@echo "🔧 Building and running BONUS tests..."
ifeq ($(FILE),)
	@$(COMPILE_ALL_BONUS)
	@$(RUN_TESTS_BONUS)
else
	@$(COMPILE_FILE_BONUS)
	@$(RUN_TESTS_BONUS)
endif

# Run the full test suite for multiple BUFFER_SIZE values
SIZES ?= 1 5 42 1000

test-all:
	@echo "🧪 Running tests for BUFFER_SIZE values: $(SIZES)"
	@for sz in $(SIZES); do \
		echo "\n=============================="; \
		echo "BUFFER_SIZE=$$sz"; \
		echo "=============================="; \
		$(MAKE) --no-print-directory clean >/dev/null; \
		$(MAKE) --no-print-directory test BUFFER_SIZE=$$sz FILE="$(FILE)" VERBOSE="$(VERBOSE)"; \
		done

test-all-bonus:
	@echo "🧪 Running BONUS tests for BUFFER_SIZE values: $(SIZES)"
	@for sz in $(SIZES); do \
		echo "\n=============================="; \
		echo "BONUS BUFFER_SIZE=$$sz"; \
		echo "=============================="; \
		$(MAKE) --no-print-directory clean >/dev/null; \
		$(MAKE) --no-print-directory test-bonus BUFFER_SIZE=$$sz FILE="$(FILE)" VERBOSE="$(VERBOSE)"; \
		done

show: VERBOSE=--verbose
show: test

show-bonus: VERBOSE=--verbose
show-bonus: test-bonus

test-list:
	@echo "📋 Listing available tests..."
	@$(COMPILE_ALL)
	@$(LD_PATH) ./$(TEST_BIN) --list

test-list-bonus:
	@echo "📋 Listing available BONUS tests..."
	@$(COMPILE_ALL_BONUS)
	@$(LD_PATH) ./$(TEST_BONUS_BIN) --list

# ---------------------------------------------------------------------------- #
# Valgrind targets                                                              #
# ---------------------------------------------------------------------------- #

valgrind:
	@echo "🕵️ Running Valgrind (BUFFER_SIZE=$(BUFFER_SIZE))..."
ifeq ($(FILE),)
	@$(COMPILE_ALL)
else
	@$(COMPILE_FILE)
endif
	@$(LD_PATH) $(VALGRIND) $(VG_OPTS) ./$(TEST_BIN) $(VERBOSE)

valgrind-all:
	@echo "🧪 Running Valgrind across BUFFER_SIZE values: $(SIZES)"
	@for sz in $(SIZES); do \
		echo "\n=============================="; \
		echo "Valgrind BUFFER_SIZE=$$sz"; \
		echo "=============================="; \
		$(MAKE) --no-print-directory clean >/dev/null; \
		$(MAKE) --no-print-directory valgrind BUFFER_SIZE=$$sz FILE="$(FILE)" VERBOSE="$(VERBOSE)" VG_OPTS="$(VG_OPTS)"; \
	 done

valgrind-bonus:
	@echo "🕵️ Running Valgrind BONUS (BUFFER_SIZE=$(BUFFER_SIZE))..."
ifeq ($(FILE),)
	@$(COMPILE_ALL_BONUS)
else
	@$(COMPILE_FILE_BONUS)
endif
	@$(LD_PATH) $(VALGRIND) $(VG_OPTS) ./$(TEST_BONUS_BIN) $(VERBOSE)

valgrind-all-bonus:
	@echo "🧪 Running Valgrind BONUS across BUFFER_SIZE values: $(SIZES)"
	@for sz in $(SIZES); do \
		echo "\n=============================="; \
		echo "Valgrind BONUS BUFFER_SIZE=$$sz"; \
		echo "=============================="; \
		$(MAKE) --no-print-directory clean >/dev/null; \
		$(MAKE) --no-print-directory valgrind-bonus BUFFER_SIZE=$$sz FILE="$(FILE)" VERBOSE="$(VERBOSE)" VG_OPTS="$(VG_OPTS)"; \
	 done

clean:
	@rm -f $(TEST_BIN)
	@echo "🧹 Removed test binary."

fclean: clean

.PHONY: all test bonus test-bonus test-all test-all-bonus show test-list test-list-bonus valgrind valgrind-all valgrind-bonus valgrind-all-bonus clean fclean