SRC = src
BIN = bin
OBJS = $(SRC)/main.o

TARGET = $(BIN)/wyskr

CC = g++
LINKER_FLAGS = -lSDL2 -lGL 

# create bin dir if it doesn't exist
#https://stackoverflow.com/questions/16344719/how-to-create-directory-if-needed
_dummy := $(shell mkdir -p $(BIN))

wyskr: src/main.o
	$(CC) $(LINKER_FLAGS) -o $(TARGET) $(SRC)/main.o 
