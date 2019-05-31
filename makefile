SRC = src
OBJ = $(SRC)/obj
BIN = bin
INCLUDE = include

CC = g++
LIBS = -lSDL2 -lGLEW -lGL  
CFLAGS = -I $(INCLUDE)

_DEPS = 
DEPS = $(patsubst %,$(INCLUDE)/%,$(_DEPS))

_OBJS = main.o
OBJS = $(patsubst %,$(OBJ)/%,$(_OBJS))

TARGET = $(BIN)/wyskr

# create bin dir if it doesn't exist
#https://stackoverflow.com/questions/16344719/how-to-create-directory-if-needed
_dummy := $(shell mkdir -p $(BIN))

$(OBJ)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
