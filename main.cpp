#include <ncurses.h>
#include "Logics.hpp"
#include "Block.hpp"

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
    Block *block = new Block(xLoc, yLoc);

    Logics::blockFalling(*block, win);

    getch();
    endwin();
    return 0;
}