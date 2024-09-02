#ifndef MENU_HPP
#define MENU_HPP

#include <chrono>

class Menu {
public:
    void showMainMenu();
    void showGameOverScreen(int totalScore, int time);

private:
    void displayScore(int totalScore);
};

#endif // MENU_HPP
