#include <ncurses.h>
#include "Logics.hpp"
#include "Block.hpp"
#include "Square.hpp"

using namespace std;
#define WIDTH 10
#define HEIGHT 20

int main(){
    initscr();
    noecho();

    int xStart = WIDTH/2;
    int yStart = 0;

    int xLoc = xStart;
    int yLoc = yStart;

    WINDOW *win = newwin(HEIGHT, WIDTH, yStart, xStart);
    //Block *block = new Block(xLoc, yLoc);

    //square->display(win);

    //Logics::blockFalling(*block, win);
    while(true){
        Square *square = new Square(xLoc, yLoc);
        Logics::squareFalling(*square, win);
        wrefresh(win);
    }

    getch();
    endwin();
    return 0;
}