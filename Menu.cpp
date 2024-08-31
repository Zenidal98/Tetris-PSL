#include "Menu.hpp"
#include <ncurses.h>
#include <iostream>
#include "Game.hpp"
#include "Leaderboard.hpp"

void Menu::showMainMenu() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int choice = 0; // User choice
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    while (true) {
        werase(stdscr);

        int start_y = max_y / 2 - 2;
        int start_x = (max_x - 20) / 2;

        mvprintw(start_y, start_x, "Welcome to Tetris!");
        mvprintw(start_y + 2, start_x, "New Game");
        mvprintw(start_y + 3, start_x, "Leaderboard");
        mvprintw(start_y + 4, start_x, "Exit");

        if (choice == 0) mvprintw(start_y + 2, start_x - 2, ">");
        else if (choice == 1) mvprintw(start_y + 3, start_x - 2, ">");
        else if (choice == 2) mvprintw(start_y + 4, start_x - 2, ">");

        wnoutrefresh(stdscr);
        doupdate();

        int ch = getch();

        switch (ch) {
            case KEY_UP:
                choice = (choice - 1 + 3) % 3;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % 3;
                break;
            case '\n':
                if (choice == 0) {
                    endwin();
                    Game game;
                    game.start();
                } else if (choice == 1) {
                    endwin();
                    Leaderboard leaderboard;
                    leaderboard.loadScores();
                    leaderboard.showLeaderboard();
                } else if (choice == 2) {
                    endwin();
                    exit(0);
                }
                return;
        }
    }
}

void Menu::showGameOverScreen(int totalScore) {
    clear();

    Leaderboard leaderboard;
    leaderboard.saveScore(totalScore);

    mvprintw(LINES / 2 - 2, COLS / 2 - 10, "Game Over");
    displayScore(totalScore);
    mvprintw(LINES / 2 + 4, COLS / 2 - 10, "Press 'q' to quit");
    mvprintw(LINES / 2 + 6, COLS / 2 - 10, "Press 'c' to play again");
    mvprintw(LINES / 2 + 8, COLS / 2 - 10, "Press 'm' to return to main menu");

    refresh();
    int ch;
    while ((ch = getch()) != 'q' && ch != 'c' && ch != 'm') {
        // Wait for input
    }

    if (ch == 'c') {
        endwin();
        Game game;
        game.start();
    } else if (ch == 'm') {
        endwin();
        showMainMenu();
    } else if (ch == 'q') {
        endwin();
        exit(0);
    }
}

void Menu::displayScore(int totalScore) const {
    mvprintw(LINES / 2, COLS / 2 - 10, "Score: %d", totalScore);
}
