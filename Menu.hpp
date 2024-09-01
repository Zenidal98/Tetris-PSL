#ifndef MENU_HPP
#define MENU_HPP

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
    void saveScore(int score);  // per la classifica private

private:
    Game* game;
};

#endif
