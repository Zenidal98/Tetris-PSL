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
    
    public:
        Square(int x, int y);
        
        Block getTopLeft() const;
        Block getTopRight() const;
        Block getBotLeft() const;
        Block getBotRight() const;
        
        void display(WINDOW *win);
        void deleteold(WINDOW *win);
        void mvsquareright(WINDOW *win);
        void mvsquareleft(WINDOW *win);
};

#endif