#include <ncurses.h>
#include "Logics.hpp"
#include "Block.hpp"
#include "Square.hpp"
// Per usare rand()
#include<string>
#include <cstdlib>
#include <ctime>

using namespace std;
#define WIDTH 10
#define HEIGHT 20

// inizializzo i colori
void initColors() {
    start_color(); // Enable color mode

    // init_pair(index, foreground, background)
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
}

int main(){
    initscr();
    noecho();
    initColors();
    srand(time(0));

    int xStart = WIDTH/2;
    int yStart = 0;

    int xLoc = xStart;
    int yLoc = yStart;

    WINDOW *playwin = newwin(HEIGHT, WIDTH, yStart, xStart);
    WINDOW *scorewin = newwin(HEIGHT, WIDTH, yStart, WIDTH+5);
    box(scorewin, 0, 0);
    string Score = "Score: "; // to_string(actualScore);
    string Time = "Time: "; // to_string(actualTime);
    //wrefresh(stdscr);

    //square->display(win);

    while(true){
        //Block *block = new Block(xLoc, yLoc, rand()%6+1);
        Square *square = new Square(xLoc, yLoc, rand()%6+1);
        //Logics::blockFalling(*block, win);
        Logics::squareFalling(*square, playwin);
        mvwprintw(scorewin,1,1,Score.c_str());
        mvwprintw(scorewin,5,1,Time.c_str());
        wrefresh(playwin);
        wrefresh(scorewin);
    }

    getch();
    endwin();
    return 0;
}
