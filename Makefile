CC:=gcc
CC_FLAGS:=-I ./include -Werror -Wall -Wextra -Wpedantic -Wcast-align -Wcast-qual -Wconversion -Wenum-compare -Wfloat-equal -Wredundant-decls -Wsign-conversion
SOURCES:=src/main.c src/shell.c src/wrappers.c src/promt.c
OUTPUT_DIR:=./build
EXECUTABLE:=shell

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):
	$(CC) $(CC_FLAGS) $(SOURCES) -o $(OUTPUT_DIR)/$(EXECUTABLE)

run: all
	./$(OUTPUT_DIR)/$(EXECUTABLE)

memcheck: all
	valgrind --leak-check=yes ./$(OUTPUT_DIR)/$(EXECUTABLE)

.PHONY: clean
clean:
	rm $(OUTPUT_DIR)/*