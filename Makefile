CC:=gcc
CC_FLAGS:=-I ./include -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
SOURCES:= src/utils.c src/builtin_functions.c src/shell.c src/wrappers.c src/promt.c src/history.c
OUTPUT_DIR:=./build
EXECUTABLE:=shell
EXECUTABLE_TEST:=shell_test

.PHONY: all run create_output_dir clean memcheck test

all: create_output_dir $(SOURCES) $(EXECUTABLE)

run: all
	./$(OUTPUT_DIR)/$(EXECUTABLE)

create_output_dir:
	mkdir -p $(OUTPUT_DIR)

clean:
	rm $(OUTPUT_DIR)/*

memcheck: test
	valgrind --leak-check=yes --track-origins=yes -s ./$(OUTPUT_DIR)/$(EXECUTABLE_TEST)

test: create_output_dir
	$(CC) $(CC_FLAGS) src/tests.c $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE_TEST)
	./$(OUTPUT_DIR)/$(EXECUTABLE_TEST)

$(EXECUTABLE):
	$(CC) $(CC_FLAGS) src/main.c $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE)
