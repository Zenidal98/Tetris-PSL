#ifndef LOGICS_HPP
#define LOGICS_HPP

#include <ncurses.h>
#include "Block.hpp"

class Logics{
    private:
        static int getInput();
    public:
        static void blockFalling(Block &block, WINDOW *win);
};

#endif