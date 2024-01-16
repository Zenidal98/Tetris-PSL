#include "Logics.hpp"

void Logics::blockFalling(Block &block, WINDOW *win){
    timeout(0);
    while(mvwinch(win, block.getyLoc()+1, block.getxLoc()) == ' '){
        block.deleteold(win);
        box(win, ACS_VLINE, ACS_HLINE);
        int ch = getInput();
        if(ch == 1){
            block.mvleft(win);
        }
        else if(ch == 2){
            block.mvright(win);
        }
        block.setyLoc(block.getyLoc()+1);
        block.display(win);
        napms(350);
    }
}

void Logics::squareFalling(Square &square, WINDOW *win){
    timeout(0);
    while( (mvwinch(win, square.getBotLeft().getyLoc()+1, square.getxLoc()) == ' ') && (mvwinch(win, square.getBotRight().getyLoc()+1, square.getxLoc()) == ' ') ){
        square.deleteold(win);
        box(win, ACS_VLINE, ACS_HLINE);
        int ch = getInput();
        if(ch == 1){
            square.mvleft(win);
        }
        else if(ch == 2){
            square.mvright(win);
        }
        square.setyLoc(square.getyLoc()+1);
        square.display(win);
        napms(350);
    }
}

// a per andare a sinistra, d per andare a destra
int Logics::getInput(){
    int ch = getch();
    switch(ch){
        case 'a':
            return 1;
        case 'd':
            return 2;
        default:
            return 0;
    }
}