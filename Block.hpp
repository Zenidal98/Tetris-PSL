#ifndef BLOCK_HPP
#define BLOCK_HPP

#define WIDTH 10
#define HEIGHT 20

#include <ncurses.h>

class Block{
    private:
        int xLoc;
        int yLoc;
        char symbol = 'O';
        // serve per dare colore
        int colorPair;
    public:
        Block(int x, int y, int color);
        int getxLoc();
        int getyLoc();

        // cambiare x e y lasciandole private
        void setxLoc(int x);
        void setyLoc(int y);

        // mostra il blocco
        void display(WINDOW *win);
        
        // cancella il blocco (utile quando si sposta il blocco)
        void deleteold(WINDOW *win);

        void mvright(WINDOW *win);
        void mvleft(WINDOW *win);

};

#endif
