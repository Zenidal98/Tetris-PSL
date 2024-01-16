#include "Block.hpp"

#define WIDTH 10
#define HEIGHT 20

Block::Block(int x, int y){
    xLoc = x;
    yLoc = y;
}

int Block::getxLoc(){
    return xLoc;
}

int Block::getyLoc(){
    return yLoc;
}

void Block::setxLoc(int x){
    if(xLoc < WIDTH){
        xLoc = 1;
    }
}

void Block::setyLoc(int y){
    yLoc = y;
}

void Block::display(WINDOW *win){
    mvwaddch(win, yLoc, xLoc, symbol);
    wrefresh(win);
}

void Block::deleteold(WINDOW *win){
    mvwaddch(win, yLoc, xLoc, ' ');
    wrefresh(win);
}

void Block::mvright(WINDOW *win){
    if(mvwinch(win, yLoc, xLoc+1) == ' '){
        xLoc++;
    }/*
    xLoc++;
    if(xLoc >= WIDTH-2){
        xLoc = WIDTH-2;
    }*/
}

void Block::mvleft(WINDOW *win){
    if(mvwinch(win, yLoc, xLoc-1) == ' '){
        xLoc--;
    }
    /*xLoc--;
    if(xLoc < 1){
        xLoc = 1;
    }*/
}