#ifndef BLOCK_HPP
#define BLOCK_HPP

#include <ncurses.h>

class Block{
    private:
        int xLoc[2];
        int yLoc;
        char symbol[2] = {'[', ']'};
    public:
        Block(int x, int y);
        int getxLoc();
        int getyLoc();
        void setxLoc(int x);
        void setyLoc(int y);
        void display(WINDOW *win);
        void deleteold(WINDOW *win);
        void mvright();
        void mvleft();
};

#endif