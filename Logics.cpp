#include "Logics.hpp"

void Logics::blockFalling(Block &block, WINDOW *win){
    // serve per non bloccare il programma quando non si preme niente
    timeout(0);
    // finchè sotto c'è spazio, continua a cadere
    while(mvwinch(win, block.getyLoc()+1, block.getxLoc()) == ' '){
        block.deleteold(win);
        // disegna il bordo (non capisco perchè è da fare tutte le volte)
        box(win, ACS_VLINE, ACS_HLINE);
        int ch = getInput();
        if(ch == 1){
            block.mvleft(win);
        }
        else if(ch == 2){
            block.mvright(win);
        }
        // sposta il blocco verso il basso
        block.setyLoc(block.getyLoc()+1);
        // mostra blocco
        block.display(win);
        // aspetta 350 millisecondi prima di riscendere 
        napms(350);
    }
}

void Logics::squareFalling(Square &square, WINDOW *win){
    timeout(0);
    // chatgpt code, controlla se sotto c'è spazio in teoria
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

        // ancora chatgpt code, dovrebbe spostare ognuno dei quattro blocchi verso il basso
        square.setyLoc(square.getyLoc()+1);
        square.getTopLeft().setyLoc(square.getyLoc());
        square.getTopRight().setyLoc(square.getyLoc());
        square.getBotLeft().setyLoc(square.getyLoc() + 1);
        square.getBotRight().setyLoc(square.getyLoc() + 1);

        // mostra quadrato
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