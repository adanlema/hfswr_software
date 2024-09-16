SRC_DIR = ./src
INC_DIR = ./inc
OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin
DOC_DIR = $(OUT_DIR)/doc

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

.DEFAULT_GOAL := all

.PHONY: clean run

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

$(OBJ_DIR): $(OUT_DIR)
	mkdir -p $(OBJ_DIR)

$(BIN_DIR): $(OUT_DIR)
	mkdir -p $(BIN_DIR)

$(DOC_DIR): $(OUT_DIR)
	mkdir -p $(DOC_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	gcc -I$(INC_DIR) -c $< -o $@ -lm

$(BIN_DIR)/app.elf: $(OBJ_FILES) | $(BIN_DIR)
	gcc -o $@ $(OBJ_FILES) -lm -ljson-c

all: $(BIN_DIR)/app.elf

clean:
	rm -rf $(OUT_DIR)

run: $(BIN_DIR)/app.elf
	$(BIN_DIR)/app.elf

doc: $(DOC_DIR)
	doxygen doxyfile