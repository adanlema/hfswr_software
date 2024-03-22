SRC_DIR = ./src
OUT_DIR = ./build
OBJ_DIR = $(OUT_DIR)/obj
BIN_DIR = $(OUT_DIR)/bin

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o,$(SRC_FILES))


.DEFAULT_GOAL := all

$(OUT_DIR):
	mkdir $(OUT_DIR)
$(OBJ_DIR) : $(OUT_DIR)
	mkdir $(OBJ_DIR)
$(BIN_DIR) : $(OUT_DIR)
	mkdir $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	gcc -c $< -o $@ -lm

all: $(OBJ_FILES) $(BIN_DIR)
	gcc -o $(BIN_DIR)/app.elf $(OBJ_FILES) -lm

clean: $(OUT_DIR)
	rm -r $(OUT_DIR)

run: $(BIN_DIR)
	$(BIN_DIR)/app.elf