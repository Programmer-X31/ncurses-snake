# Compiler
CC = gcc
DEBUGGER = gdb

# Compiler flags
CFLAGS = -Wall -Wextra -g -Isrc

# Production objects, excluding the game's main function.
LIB_OBJECTS = $(filter-out $(BIN_DIR)/main.o,$(OBJECTS))

# Convert tests/snake_test.c into bin/snake_test.test.o.
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%.test.o,$(TESTS))

# Test-specific compiler and linker flags.
TESTFLAGS = -Wpedantic -fsanitize=address,undefined -DDEBUG

# Linker libraries
LDLIBS = -lncurses

# Directories
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests

# Executable
TARGET = $(BIN_DIR)/snake
TEST_TARGET = $(BIN_DIR)/snake-test

# Source and object files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCES))
TESTS = $(wildcard $(TEST_DIR)/*.c)

# Default target
.PHONY: all
all: $(TARGET)

# Link object files
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Compile source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Create bin directory
$(BIN_DIR):
	mkdir -p $@


.PHONY: test
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Link test objects with production modules.
$(TEST_TARGET): $(TEST_OBJECTS) $(LIB_OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^ $(LDLIBS)

# Compile each test source into a separate object.
$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.c | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TESTFLAGS) -c $< -o $@

# Clean build artifacts
.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
