CC:=gcc
CC_FLAGS:=-I ./include -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
SOURCES:=src/shell.c src/wrappers.c src/promt.c
OUTPUT_DIR:=./build
EXECUTABLE:=shell
EXECUTABLE_TEST:=shell_test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CC_FLAGS) src/main.c $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE)

run: all
	./$(OUTPUT_DIR)/$(EXECUTABLE)

test: 
	$(CC) $(CC_FLAGS) src/tests.c $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE_TEST)
	./$(OUTPUT_DIR)/$(EXECUTABLE_TEST)

memcheck: test
	valgrind --leak-check=yes --track-origins=yes ./$(OUTPUT_DIR)/$(EXECUTABLE_TEST)

.PHONY: clean
clean:
	rm $(OUTPUT_DIR)/*