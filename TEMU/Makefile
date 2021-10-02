include mips_sc/src/Makefile.testcase

.PHONY: run clean build

ifndef INCLUDE_DIR
INCLUDE_DIR := ./temu/include
endif
ifndef SRC_DIR
SRC_DIR := ./temu/src
endif
ifndef BUILD_DIR
BUILD_DIR := build/
endif
DEBUG := true

# Compilation flags
CC := gcc
CFLAGS := -I$(INCLUDE_DIR) -I$(INCLUDE_DIR)/cpu -I$(INCLUDE_DIR)/memory -I$(INCLUDE_DIR)/monitor -Wall -Werror  
LDFLAGS := -lreadline

# Files to be compiled
SRCS := $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/memory/*.c) $(wildcard $(SRC_DIR)/cpu/*.c) $(wildcard $(SRC_DIR)/monitor/*.c)

TEMU_TARGET := temu

ifeq ($(DEBUG), true)
CFLAGS += -g
endif

export	INCLUDE_DIR
export	SRC_DIR
export	BUILD_DIR

# ********************
# Rules of Compilation
# ********************

default: clean build 

# $(BUILD_DIR)$(TEMU_TARGET):
# @mkdir -p $(BUILD_DIR)
build:
	@mkdir  $(BUILD_DIR)
# 这里，要把-lreadline 放到后面才可以！！！
	$(CC) $(CFLAGS)  -o $(BUILD_DIR)$(TEMU_TARGET) $(SRCS) $(LDFLAGS)


run: $(BUILD_DIR)$(TEMU_TARGET)
	@./$(BUILD_DIR)$(TEMU_TARGET) $(USER_PROGRAM)

clean:
	rm -f -r $(BUILD_DIR)
	rm -f -r ./mips_sc/build
	rm -f log.txt

cleanins:
	rm -f *.bin

gdb:
	gdb build/temu
