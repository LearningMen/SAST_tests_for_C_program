# Compiler and compiler flags
CC=gcc
CFLAGS=-Wall -g

# Find all .c files in the current directory
SOURCES=$(wildcard *.c)

# Determine the executable names for each source file
EXECUTABLES=$(SOURCES:.c=)

# Default target to build all executables
all: $(EXECUTABLES)

# Rule to compile each source file to an executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Clean up the built executables
clean:
	rm -f $(EXECUTABLES)
