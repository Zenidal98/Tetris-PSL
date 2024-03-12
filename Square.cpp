#include "Square.hpp"

// chatgpt code, crea quadrato 2x2 blocchi
Square::Square(int x, int y, int color): Block(x, y, color), topLeft(x,y, color), topRight(x+1,y, color), botLeft(x,y+1, color), botRight(x+1,y+1, color){
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
    if(topRight.getxLoc() < WIDTH-2){
        if(mvwinch(win, topRight.getyLoc(), topRight.getxLoc()+1) == ' ' && mvwinch(win, botRight.getyLoc(), botRight.getxLoc()+1) == ' '){
            topLeft.mvright(win);
            topRight.mvright(win);
            botLeft.mvright(win);
            botRight.mvright(win);
        }
    }
}

void Square::mvsquareleft(WINDOW *win){
    if(topLeft.getxLoc() > 0){
        if(mvwinch(win, topLeft.getyLoc(), topLeft.getxLoc()-1) == ' ' && mvwinch(win, botLeft.getyLoc(), botLeft.getxLoc()-1) == ' '){
            topLeft.mvleft(win);
            topRight.mvleft(win);
            botLeft.mvleft(win);
            botRight.mvleft(win);
        }
    }
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

void Square::setTopLeft(int x, int y){
    topLeft.setxLoc(x);
    topLeft.setyLoc(y);
}

void Square::setTopRight(int x, int y){
    topRight.setxLoc(x);
    topRight.setyLoc(y);
}

void Square::setBotLeft(int x, int y){
    botLeft.setxLoc(x);
    botLeft.setyLoc(y);
}

void Square::setBotRight(int x, int y){
    botRight.setxLoc(x);
    botRight.setyLoc(y);
}

void Square::mvsquaredown(WINDOW *win){
    if(botLeft.getyLoc() < HEIGHT-1){
        if(mvwinch(win, botLeft.getyLoc()+1, botLeft.getxLoc()) == ' ' && mvwinch(win, botRight.getyLoc()+1, botRight.getxLoc()) == ' '){
            topLeft.mvdown(win);
            topRight.mvdown(win);
            botLeft.mvdown(win);
            botRight.mvdown(win);
        }
    }
}