#include <ncurses.h>
#include <iostream>
#include "Menu.hpp"
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

        mvprintw(start_y, start_x, "Benvenuto a Tetris !");
        mvprintw(start_y + 2, start_x, "Nuova Partita");
        mvprintw(start_y + 3, start_x, "Classifica");
        mvprintw(start_y + 4, start_x, "Esci");

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
                    clear();
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

void Menu::showGameOverScreen(int totalScore, int time) {
    clear();

    totalScore=totalScore+time/2;

    Leaderboard leaderboard;
    leaderboard.saveScore(totalScore);

    mvprintw(LINES / 2 - 2, COLS / 2 - 10, "Game Over");
    displayScore(totalScore);
    mvprintw(LINES / 2 + 4, COLS / 2 - 10, "Premi Q per uscire ");
    mvprintw(LINES / 2 + 6, COLS / 2 - 10, "Premi C per fare un'altra partita");
    mvprintw(LINES / 2 + 8, COLS / 2 - 10, "Premi M per tornare al menù principale");

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

void Menu::displayScore(int totalScore) {
    mvprintw(LINES / 2, COLS / 2 - 10, "Punteggio: %d", totalScore);
}
