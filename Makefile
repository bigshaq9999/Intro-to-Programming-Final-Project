CC = clang
CFLAGS = -Wall -Wextra -pedantic -std=c11

# List of source files
SRCS = final-proj.c functions.c 

# List of object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = final-proj 

all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJS)
		$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

# Rule to build object files from source files
%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -f $(OBJS) $(TARGET)
