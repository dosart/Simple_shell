CC := gcc
CC_FLAGS := -I ./include -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion

OUTPUT_DIR = ./build

all: shell

shell: src/shell.c include/shell.h include/wrappers.h
	$(CC) $(CC_FLAGS) src/main.c src/shell.c src/wrappers.c src/promt.c -o $(OUTPUT_DIR)/shell

.PHONY: clean
cleam:
	rm $(OUTPUT_DIR)/*