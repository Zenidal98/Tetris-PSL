#include "Block.hpp"

#define WIDTH 10
#define HEIGHT 20

Block::Block(int x, int y){
    xLoc[0] = x;
    xLoc[1] = x+1;
    yLoc = y;
}

int Block::getxLoc(){
    return xLoc[0];
}

int Block::getyLoc(){
    return yLoc;
}

void Block::setxLoc(int x){
    if(xLoc[1]+1 < WIDTH){
        xLoc[0] = x;
        xLoc[1] = x+1;
    }
}

void Block::setyLoc(int y){
    yLoc = y;
}

void Block::display(WINDOW *win){
    mvwaddch(win, yLoc, xLoc[0], symbol[0]);
    mvwaddch(win, yLoc, xLoc[1], symbol[1]);
    wrefresh(win);
}

void Block::deleteold(WINDOW *win){
    mvwaddch(win, yLoc, xLoc[0], ' ');
    mvwaddch(win, yLoc, xLoc[1], ' ');
    wrefresh(win);
}

void Block::mvright(){
    xLoc[0]++;
    xLoc[1]++;
    if(xLoc[1] >= WIDTH-1){
        xLoc[1] = WIDTH-2;
        xLoc[0] = WIDTH-3;
    }
}

void Block::mvleft(){
    xLoc[0]--;
    xLoc[1]--;
    if(xLoc[0] < 1){
        xLoc[0] = 1;
        xLoc[1] = 2;
    }
}