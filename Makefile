CC = g++

CFLAGS = -std=c++11 -g -Wall -Wextra

LIBS = -lncurses

Tetris-PSL: main.o Block.o Square.o Logics.o Menu.o
	g++ main.o Block.o Square.o Logics.o Menu.o Tutils.o -o Tetris-PSL $(LIBS)

main.o: main.cpp
	g++ -c main.cpp

Block.o: Block.cpp
	g++ -c Block.cpp

Square.o: Square.cpp
	g++ -c Square.cpp

Logics.o: Logics.cpp
	g++ -c Logics.cpp

Menu.o:Menu.cpp
	g++ -c Menu.cpp

Tutils.o:Tutils.cpp
	g++ -c Tutils.cpp

clean:
	rm -f *.o Tetris-PSL
