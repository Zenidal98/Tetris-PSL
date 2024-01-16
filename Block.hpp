#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <ncurses.h>

class Block{
    private:
        int xLoc;
        int yLoc;
        char symbol = 'O';
    public:
        Block(int x, int y);
        int getxLoc();
        int getyLoc();
        void setxLoc(int x);
        void setyLoc(int y);
        void display(WINDOW *win);
        void deleteold(WINDOW *win);
        void mvright(WINDOW *win);
        void mvleft(WINDOW *win);
};

#endif