# Compiler and compiler flags
CC=gcc
CFLAGS=-Wall -g
SQLITE_LIB=-lsqlite3
PTHREAD_LIB=-lpthread

# Find all .c files in the current directory
SOURCES=$(wildcard *.c)

# Determine the executable names for each source file
EXECUTABLES=$(SOURCES:.c=)

# Default target to build all executables
all: $(EXECUTABLES)

# Rule to compile each source file to an executable
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# Special rule for SQL_injection to link the SQLite library
SQL_injection: SQL_injection.c
	$(CC) $(CFLAGS) -o $@ $< $(SQLITE_LIB)
	
# Special rule for race_condition to link the pthread library
race_condition: race_condition.c
	$(CC) $(CFLAGS) -o $@ $< $(PTHREAD_LIB)
# Clean up the built executables
clean:
	rm -f $(EXECUTABLES)
