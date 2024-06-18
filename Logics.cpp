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


        //codice di prova per andare verso il basso
        else if(ch == 3){
            block.mvdown(win);
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
            square.mvsquareleft(win);
        }
        else if(ch == 2){
            square.mvsquareright(win);
        }


        // codice di prova per basso
        else if(ch == 3){
            square.mvsquaredown(win);
        }

        // ancora chatgpt code, dovrebbe spostare ognuno dei quattro blocchi verso il basso
        square.setTopLeft(square.getTopLeft().getxLoc(), square.getTopLeft().getyLoc()+1);
        square.setTopRight(square.getTopRight().getxLoc(), square.getTopRight().getyLoc()+1);
        square.setBotLeft(square.getBotLeft().getxLoc(), square.getBotLeft().getyLoc()+1);
        square.setBotRight(square.getBotRight().getxLoc(), square.getBotRight().getyLoc()+1);

        // mostra quadrato
        square.display(win);
        napms(200);
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
        case 's':
            return 3;
        default:
            return 0;
    }
}



void Logics::checkRows(WINDOW *win){
     for(int y=0; y<21; y++){
         bool full = true;               // assumiamo la riga piena
         for(int x=0; x<11; x++){
             char ch = mvwinch(win, y, x) & A_CHARTEXT;
             if(ch!='O'){
                full = false;
             }
         }
         if(full == true){
                                            //copiamo quello che c'è sopra con una nuova variabile
            for(int r=y; r>0; r--){
               for(int x=0; x<11; x++){
                  char ch=mvwinch(win, r-1,x) & A_CHARTEXT;
                  mvwaddch(win, r, x, ch);  //copia il carattere nella riga corrente
               }
            }
                                            //cancella la prima riga
            for (int x = 0; x < 10; x++) {
                    mvwaddch(win, 0, x, ' ');
            }
         wrefresh(win);
         }
     }
}



