SRC = src
OBJ = $(SRC)/obj
BIN = bin
INCLUDE = include

CC = g++
LIBS = -lSDL2 -lGLEW -lGL  
CFLAGS = -I $(INCLUDE)

_DEPS = glshader.hpp
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

_OBJS = main.o glshader.o
OBJS = $(patsubst %,$(OBJ)/%,$(_OBJS))

TARGET = $(BIN)/wyskr

# create dirs if they doesn't exist
#https://stackoverflow.com/questions/16344719/how-to-create-directory-if-needed
_dummy := $(shell mkdir -p $(BIN))
_dummy := $(shell mkdir -p $(OBJ))

$(OBJ)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
