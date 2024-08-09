#compiler and flags

CC=gcc
CFLAGS = -Wall -Wextra -std=c11 -g

#output executable
TARGET = emulator_test1

#source directory
SRC_DIR = ./src

#source files
SRCS = ${SRC_DIR}/cpu.c ${SRC_DIR}/bus.c  ${SRC_DIR}/memory.c  ${SRC_DIR}/instructions.c

#defining object files
OBJS = ${SRCS:.c=.o}

#header files
HDRS = ${SRC_DIR}/cpu.h ${SRC_DIR}/bus.h  ${SRC_DIR}/memory.h  ${SRC_DIR}/instructions.h

#default rule
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

#rule to built object files
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

#clean
clean:
	rm -f $(OBJS)

#phony targets
.PHONY: clean