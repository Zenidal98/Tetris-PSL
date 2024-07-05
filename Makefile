CC = g++

CFLAGS = -std=c++11 -g -Wall -Wextra

LIBS = -lncurses

Tetris-PSL: main.o Logics.o Menu.o Tutils.o Grid.o
	g++ main.o Logics.o Menu.o Tutils.o Grid.o -o Tetris-PSL $(LIBS)

main.o: main.cpp
	g++ -c main.cpp

Logics.o: Logics.cpp
	g++ -c Logics.cpp

Menu.o:Menu.cpp
	g++ -c Menu.cpp

Tutils.o:Tutils.cpp
	g++ -c Tutils.cpp

Grid.o:Grid.cpp 
	g++ -c Grid.cpp 
clean:
	rm -f *.o Tetris-PSL
