MY_PATH=$(shell pwd)
TARGET=process
#CC=g++
CC=gcc

SRC=$(shell ls *.c)
OBJ_O=$(SRC:.c=.o)

INCLUDE=./
LIB=./

$(TARGET):$(OBJ_O)
	@echo "[$@] begin building .. done"
	@$(CC) -o $(TARGET) $(OBJ_O) -L$(LIB)
%.o:%.c
	@echo "[$@] begin compliing..done"
	@$(CC) -c $< -I$(INCLUDE)

.PHONY:clean
clean:
	@rm -rf *.o $(TARGET)

