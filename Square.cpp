#include "Square.hpp"

Square::Square(int x, int y): Block(x, y), topLeft(x,y), topRight(x+1,y), botLeft(x,y+1), botRight(x+1,y+1){
}

void Square::display(WINDOW *win){
    topLeft.display(win);
    topRight.display(win);
    botLeft.display(win);
    botRight.display(win);
}

void Square::deleteold(WINDOW *win){
    topLeft.deleteold(win);
    topRight.deleteold(win);
    botLeft.deleteold(win);
    botRight.deleteold(win);
}

void Square::mvsquareright(WINDOW *win){
    topLeft.mvright(win);
    topRight.mvright(win);
    botLeft.mvright(win);
    botRight.mvright(win);
}

void Square::mvsquareleft(WINDOW *win){
    topLeft.mvleft(win);
    topRight.mvleft(win);
    botLeft.mvleft(win);
    botRight.mvleft(win);
}

Block Square::getTopLeft() const{
    return topLeft;
}

Block Square::getTopRight() const{
    return topRight;
}

Block Square::getBotLeft() const{
    return botLeft;
}

Block Square::getBotRight() const{
    return botRight;
}