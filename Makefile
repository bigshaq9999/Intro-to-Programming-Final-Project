CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c11 -I include

# List of source files
SRC = src/final-proj.c src/io.c src/utils.c src/calculations.c

# List of object files
OBJ = $(SRC:.c=.o)

# Name of the executable
EXEC = final-proj

# Default target
all: $(EXEC)

# Linking the object files
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling the source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning up
clean:
	rm -f $(OBJ) $(EXEC)

# Dependencies
final-proj.o: include/functions.h
io.o: include/io.h
calculations.o: include/calculations.h
utils.o: include/utils.h

# EOF
