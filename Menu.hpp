#ifndef MENU_HPP
#define MENU_HPP

#include "Game.hpp"
#include <ncurses.h>
#include <chrono>
#include <fstream>
#include <vector>
#include <algorithm>

class Menu {
public:
    Menu(Game* game); 

    void showGameOverScreen();
    void showGameMenu();
    void showLeaderboard();

private:
    Game* game;
};

#endif
