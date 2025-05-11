CC = gcc
CFLAGS = -Wall -Wextra -Werror -Wpedantic -std=c99
LDFLAGS =
SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
EXEC = $(BIN_DIR)/out

$(shell mkdir -p $(OBJ_DIR) $(BIN_DIR))

SOURCES := $(shell find $(SRC_DIR) -name "*.c")
OBJECTS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))

DEPS := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.d,$(SOURCES))

all: build debug

build release: CFLAGS += -O2
build release: $(EXEC)

build debug: CFLAGS += -g
build debug: $(EXEC)

$(EXEC): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

memtest: $(EXEC)
	valgrind -s --leak-check=full --track-origins=yes --error-exitcode=1 --show-leak-kinds=all $(EXEC)

clean:
	rm -rf ./$(BUILD_DIR)

.PHONY: all build release debug memtest clean
