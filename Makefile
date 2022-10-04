CC:=gcc
CC_FLAGS:=-I ./include -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
SOURCES:=src/shell.c src/wrappers.c src/promt.c
OUTPUT_DIR:=./build
EXECUTABLE:=shell
EXECUTABLE_TEST:=shell_test

.PHONY: all run creater_output_dir clean memcheck test

all: creater_output_dir $(SOURCES) $(EXECUTABLE)

run: all
	./$(OUTPUT_DIR)/$(EXECUTABLE)

creater_output_dir:
	[ -d $(OUTPUT_DIR) ] && mkdir $(OUTPUT_DIR)

clean:
	rm $(OUTPUT_DIR)/*

memcheck: test
	valgrind --leak-check=yes --track-origins=yes ./$(OUTPUT_DIR)/$(EXECUTABLE_TEST)

test: creater_output_dir
	$(CC) $(CC_FLAGS) src/tests.c $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE_TEST)
	./$(OUTPUT_DIR)/$(EXECUTABLE_TEST)

$(EXECUTABLE):
	$(CC) $(CC_FLAGS) src/main.c $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE)
