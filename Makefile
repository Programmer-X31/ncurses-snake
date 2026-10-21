# Compiler
CC = gcc
DEBUGGER = gdb

# Compiler flags
CFLAGS = -Wall -Wextra -g -Isrc
TESTFLAGS = -Wpedantic -fsanitize=address,undefined -DDEBUG

# Linker libraries
LDLIBS = -lncurses

# Directories
SRC_DIR = src
BIN_DIR = bin
TEST_DIR = tests

# Executables
TARGET = $(BIN_DIR)/snake
TEST_TARGET = $(BIN_DIR)/snake-test

# Source, header, and object files
SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCES))

TESTS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJECTS = $(patsubst $(TEST_DIR)/%.c,$(BIN_DIR)/%.test.o,$(TESTS))

# Production objects, excluding main
LIB_OBJECTS = $(filter-out $(BIN_DIR)/main.o,$(OBJECTS))

# Debug versions of production objects for tests
DEBUG_LIB_OBJECTS = $(patsubst $(BIN_DIR)/%.o,$(BIN_DIR)/%.debug.o,$(LIB_OBJECTS))

.PHONY: all test clean

all: $(TARGET)

# Normal executable
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)

# Normal production objects
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Test executable
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(DEBUG_LIB_OBJECTS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TESTFLAGS) -o $@ $^ $(LDLIBS)

# Compile test sources with DEBUG enabled
$(BIN_DIR)/%.test.o: $(TEST_DIR)/%.c $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TESTFLAGS) -c $< -o $@

# Compile production modules with DEBUG enabled for tests
$(BIN_DIR)/%.debug.o: $(SRC_DIR)/%.c $(HEADERS) | $(BIN_DIR)
	$(CC) $(CFLAGS) $(TESTFLAGS) -c $< -o $@

# Create bin directory
$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)