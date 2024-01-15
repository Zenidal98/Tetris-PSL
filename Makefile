CC = g++

CFLAGS = -std=c++11 -g -Wall -Wextra

LIBS = -lncurses

Tetris-PSL: main.o Logics.o
	g++ main.o Logics.o -o Tetris-PSL $(LIBS)

maintest.o: main.cpp
	g++ -c maintest.cpp

Logics.o: Logics.cpp
	g++ -c Logics.cpp

clean: rm *.o Tetris-PSL
