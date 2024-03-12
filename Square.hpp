#ifndef SQUARE_HPP
#define SQUARE_HPP

#include "Block.hpp"
#include <ncurses.h>

class Square: public Block{
    private:
        Block topLeft;
        Block topRight;
        Block botLeft;
        Block botRight;
        int colorPair;
    
    public:
        Square(int x, int y, int color);
        
        Block getTopLeft() const;
        Block getTopRight() const;
        Block getBotLeft() const;
        Block getBotRight() const;
        
        void display(WINDOW *win);
        void deleteold(WINDOW *win);
        void mvsquareright(WINDOW *win);
        void mvsquareleft(WINDOW *win);
        void mvsquaredown(WINDOW *win);

        //chatgpt
        void setTopLeft(int x, int y);
        void setTopRight(int x, int y);
        void setBotLeft(int x, int y);
        void setBotRight(int x, int y);
};

#endif