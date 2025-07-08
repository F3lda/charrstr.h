# Dynamic String Library Makefile
# Supports both Windows (MinGW/MSYS2) and Linux/Unix systems

# Detect operating system
ifeq ($(OS),Windows_NT)
    DETECTED_OS := Windows
    EXE_EXT := .exe
    RM := del /Q
    MKDIR := mkdir
    PATH_SEP := \\
else
    DETECTED_OS := $(shell uname -s)
    EXE_EXT :=
    RM := rm -f
    MKDIR := mkdir -p
    PATH_SEP := /
endif

# Compiler settings
CC := gcc
CFLAGS := -Wall -Wextra -std=c99 -O2 -Isrc
DEBUG_CFLAGS := -Wall -Wextra -std=c99 -g -DDEBUG -O0 -Isrc
LDFLAGS :=

# Directories
SRC_DIR := src
BUILD_DIR := build

# Source files
MAIN_SRC := main.c
LIB_SRC := $(SRC_DIR)$(PATH_SEP)charrstr.c
HEADERS := $(SRC_DIR)$(PATH_SEP)charrstr.h

# Target executable
TARGET := $(BUILD_DIR)$(PATH_SEP)charrstr_test$(EXE_EXT)
DEBUG_TARGET := $(BUILD_DIR)$(PATH_SEP)charrstr_test_debug$(EXE_EXT)

# Default target
all: $(TARGET)

# Create build directory
$(BUILD_DIR):
ifeq ($(DETECTED_OS),Windows)
	@if not exist "$(BUILD_DIR)" $(MKDIR) "$(BUILD_DIR)"
else
	@$(MKDIR) $(BUILD_DIR)
endif

# Build release version
$(TARGET): $(BUILD_DIR) $(MAIN_SRC) $(LIB_SRC) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(MAIN_SRC) $(LIB_SRC) $(LDFLAGS)

# Build debug version
debug: $(DEBUG_TARGET)

$(DEBUG_TARGET): $(BUILD_DIR) $(MAIN_SRC) $(LIB_SRC) $(HEADERS)
	$(CC) $(DEBUG_CFLAGS) -o $@ $(MAIN_SRC) $(LIB_SRC) $(LDFLAGS)

# Run the program
run: $(TARGET)
ifeq ($(DETECTED_OS),Windows)
	@$(TARGET)
else
	@./$(TARGET)
endif

# Clean build artifacts
clean:
ifeq ($(DETECTED_OS),Windows)
	@if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
else
	@$(RM) -r $(BUILD_DIR)
endif

# Phony targets
.PHONY: all debug run clean

# Special rules for Windows
ifeq ($(DETECTED_OS),Windows)
.SUFFIXES: .exe
endif
