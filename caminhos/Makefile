EXE = main

C++ = g++
SRC_DIR = sources
OBJ_DIR = obj
TDD_DIR = tratamento_tsp

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TDD = $(TDD_DIR)/main.cpp

CFLAGS = -std=c++11 -Wall -Wextra
CFLAGS += -g

.PHONY: all tdd clean

all: $(EXE)

$(EXE): $(OBJ)
	$(C++) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(C++) $(CFLAGS) -c $< -o $@

tdd:
	g++ $(TDD) $(CFLAGS) -o $(TDD_DIR)/$@

clean:
	rm $(OBJ)
	rm $(EXE)
	rm $(TDD_DIR)/tdd