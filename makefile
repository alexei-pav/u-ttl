TARGET = u-ttl

CC = gcc
OBJCOPY = objcopy

CFLAGS = -c -g -Iinclude/

SRC_C_DIR = src/
OBJ_DIR = bin/obj/
OUT_DIR = bin/

SCR_C = $(wildcard $(SRC_C_DIR)*.c)
OBJ_C = $(patsubst $(SRC_C_DIR)%.c, $(OBJ_DIR)%.o, $(SCR_C)) 

all: $(TARGET)

$(TARGET): $(OBJ_C)
	$(CC) $(OBJ_ASM) $(OBJ_C) -o $(OUT_DIR)/$(TARGET).elf
	@echo "\033[97;100;1mDone!\033[0m"

$(OBJ_DIR)%.o: $(SRC_C_DIR)%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@
	@echo "\033[32;1m$< OK\033[0m"

$(OBJ_DIR):
	mkdir $(OUT_DIR)
	mkdir $(OBJ_DIR)
clean:
	rm -rf $(OBJ_DIR)*.o
	rm -rf $(OUT_DIR)*.bin $(OUT_DIR)*.elf
