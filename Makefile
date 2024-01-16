CC = g++

CFLAGS = -std=c++11 -g -Wall -Wextra

LIBS = -lncurses

Tetris-PSL: main.o Block.o Square.o Logics.o
	g++ main.o Block.o Square.o Logics.o -o Tetris-PSL $(LIBS)

maintest.o: main.cpp
	g++ -c maintest.cpp

Block.o: Block.cpp
	g++ -c Block.cpp

Square.o: Square.cpp
	g++ -c Square.cpp

Logics.o: Logics.cpp
	g++ -c Logics.cpp

clean: rm *.o Tetris-PSL
