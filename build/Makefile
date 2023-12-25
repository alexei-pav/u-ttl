TARGET = u-ttl

CC = gcc
OBJCOPY = objcopy

CFLAGS = -c -g -I../src/inc/ 

SRC_C_DIR = ../src/
OBJ_DIR = ../obj/
OUT_DIR = ../out/

SCR_C = $(wildcard $(SRC_C_DIR)*.c)
OBJ_C = $(patsubst $(SRC_C_DIR)%.c, $(OBJ_DIR)%.o, $(SCR_C)) 


$(TARGET): $(OBJ_C) $(OBJ_ASM)
	@echo "\033[32;1mObject files OK\033[0m"
	$(CC) $(OBJ_ASM) $(OBJ_C) -o $(OUT_DIR)/$(TARGET).elf
	@echo "\033[97;100;1mDone!\033[0m"

$(OBJ_DIR)%.o: $(SRC_C_DIR)%.c
	$(CC) $(CFLAGS) $< -o $@

run:
	../out/$(TARGET).elf 9600 /dev/USB0

clean:
	rm -rf $(OBJ_DIR)*.o
	rm -rf $(OUT_DIR)*.bin $(OUT_DIR)*.elf