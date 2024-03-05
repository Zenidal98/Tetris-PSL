#ifndef LOGICS_HPP
#define LOGICS_HPP

#include <ncurses.h>
#include "Block.hpp"
#include "Square.hpp"

class Logics{
    private:
        // prende dad tastiera per spostare destra sinistra
        static int getInput();
    public:
        // caduta blocco verso il basso
        static void blockFalling(Block &block, WINDOW *win);
        // caduta quadrato (4 blocchi)
        static void squareFalling(Square &square, WINDOW *win);
};

#endif