SRC = src
OBJ = obj
BIN = bin
RES = res

CC = g++
LIBS = -lSDL2 -lGLEW -lGL  
CFLAGS = -I $(SRC)

_DEPS = ecs.hpp cuberenderercomponent.hpp renderercomponent.hpp camera.hpp screen.hpp core.hpp util.hpp time.hpp vertex.hpp colour.hpp framework.hpp 
DEPS = $(patsubst %,$(SRC)/%,$(_DEPS))

_OBJS = cuberenderercomponent.o renderercomponent.o camera.o screen.o util.o time.o colour.o framework.o 
OBJS = $(patsubst %,$(OBJ)/%,$(_OBJS))

TARGET = $(BIN)/wyskr

# create dirs if they doesn't exist
#https://stackoverflow.com/questions/16344719/how-to-create-directory-if-needed
_dummy := $(shell mkdir -p $(BIN))
_dummy := $(shell mkdir -p $(OBJ))

# perform build and
# copy resources to build dir
$(TARGET): $(OBJS) 
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	cp -r $(RES) $(BIN)

$(OBJ)/%.o: $(SRC)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
	-rm -r $(OBJ) $(BIN) 
