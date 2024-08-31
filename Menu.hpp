#ifndef MENU_HPP
#define MENU_HPP

#include <chrono>

class Menu {
public:
    void showMainMenu();
    void showGameOverScreen(int totalScore);

private:
    void displayScore(int totalScore) const;
};

#endif // MENU_HPP
