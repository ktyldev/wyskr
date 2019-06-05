SRC_DIR = src
BIN_DIR = bin
RES_DIR = res

# executable
TARGET = $(BIN_DIR)/wyskr
CC = g++
LIBS = $(pkg-config --static --libs gl glew sdl2)  

CFLAGS = -I$(SRC_DIR) -std=c++17 -Wall

SRC = $(shell find $(SRC_DIR) -name *.cpp)
OBJ = $(SRC:%.cpp=%.o)

# create dirs if they doesn't exist
#https://stackoverflow.com/questions/16344719/how-to-create-directory-if-needed
_dummy := $(shell mkdir -p $(BIN_DIR))

# perform build and
# copy resources to build dir
$(TARGET): $(OBJ) 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	cp -r $(RES_DIR) $(BIN_DIR)

%.o: %.cpp 
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	-rm -r $(OBJ) $(BIN_DIR) 

run: $(TARGET)
	$(TARGET)

.PHONY: run clean
