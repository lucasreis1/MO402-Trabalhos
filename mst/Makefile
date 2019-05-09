EXEC_NAME = main

C++ = g++
SRC_DIR = sources
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CFLAGS = -std=c++11 -Wall

.PHONY: all clean

all: EXE

EXE: $(OBJ)
	$(C++) $^ -o $(EXEC_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(C++) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJ)