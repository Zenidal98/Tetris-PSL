#include "Leaderboard.hpp"
#include "Menu.hpp"
#include <ncurses.h>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

void Leaderboard::loadScores() {
    std::ifstream infile("scores.txt");
    int score;
    scores.clear();
    while (infile >> score) {
        scores.push_back(score);
    }
    std::sort(scores.rbegin(), scores.rend());
}

void Leaderboard::saveScore(int score) {
    std::ofstream outfile("scores.txt", std::ios::app);
    outfile << score << std::endl;
}

void Leaderboard::showLeaderboard() {
    clear();  // Clear the screen for the leaderboard

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    mvprintw(1, max_x / 2 - 6, "Leaderboard");

    int start_y = 3;
    for (size_t i = 0; i < scores.size() && i < 10; ++i) {
        mvprintw(start_y + i, max_x / 2 - 10, "%zu. %d", i + 1, scores[i]);
    }

    mvprintw(start_y + 12, max_x / 2 - 10, "Press 'm' to return to main menu");

    refresh();

    int ch;
    while ((ch = getch()) != 'm') {
        // Aspetta che l'utente prema 'm'
    }

    // Torna al menu principale
    Menu menu;
    menu.showMainMenu();
}
