TARGET := shell-cmd

#  SRC_DIR := src
#  INCLUDE_DIR := include
#  BIN_DIR := bin
#  OBJ_DIR := obj

SRCS := $(shell find ./src -type f -name *.c)
HEADS := $(shell find ./include -type f -name *.h)
OBJS := $(SRCS:src/%.c=build/%.o)
INCLUDES := -I./include

OBJ_DIR := $(./build/*)

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	gcc -l -o $@ $(OBJS)

run: all
	@./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
