TARGET := shell-cmd

#  SRC_DIR := src
#  INCLUDE_DIR := include
#  BIN_DIR := bin
#  OBJ_DIR := obj

SRCS := $(shell find ./src -type f -name *.c)
HEADS := $(shell find ./include -type f -name *.h)
OBJS := $(SRCS:src/%.c=build/%.o)
INCLUDES := -I./include

all: $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	gcc -o $@ $(OBJS)

#  run: all
	#  @./$(TARGET)

.PHONY: clean
clean:
	rm -rf $(TARGET)
