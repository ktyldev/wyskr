SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
RES_DIR = res

# executable
TARGET = $(BIN_DIR)/wyskr
CC = g++
LIBS = -lSDL2 -lGLEW -lGL  

CFLAGS = -I$(SRC_DIR)

SRC = $(shell find . -name *.cpp)
OBJ = $(SRC:%.cpp=%.o)

# create dirs if they doesn't exist
#https://stackoverflow.com/questions/16344719/how-to-create-directory-if-needed
_dummy := $(shell mkdir -p $(BIN_DIR))
_dummy := $(shell mkdir -p $(OBJ_DIR))

# perform build and
# copy resources to build dir
$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	cp -r $(RES_DIR) $(BIN_DIR)

%.o: %.cpp 
	$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	-rm -r $(OBJ) $(BIN_DIR) 
