CXX = g++
CXXFLAGS = -std=c++11 -lncurses

LIBS = -lncurses

SRC = src/main.cpp src/Tutils.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = tetris

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJ) $(TARGET)
