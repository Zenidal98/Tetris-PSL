#include "Leaderboard.hpp"
#include "Menu.hpp"
#include <ncurses.h>
#include <fstream>

void Leaderboard::loadScores() {
    std::ifstream infile("scores.txt");
    int score;
    num_scores = 0;                       // Reset del conteggio

    while (infile >> score) {
        if (num_scores < max_scores) {
            scores[num_scores++] = score;
        }
    }

    bubbleSort();
}

void Leaderboard::saveScore(int score) {

    loadScores();

    if (num_scores < max_scores) {
        scores[num_scores++] = score;
    } else if (score > scores[num_scores - 1]) {     // Se il punteggio è maggiore del più basso nella classifica
        scores[num_scores - 1] = score;              // Sostituisci il più basso
    }

    bubbleSort();

                                                      // Sovrascrivi il file con i nuovi punteggi ordinati
    std::ofstream outfile("scores.txt");
    for (int i = 0; i < num_scores; ++i) {
        outfile << scores[i] << std::endl;
    }
}

void Leaderboard::bubbleSort() {
    bool swapped;
    for (int i = 0; i < num_scores - 1; ++i) {
        swapped = false;
        for (int j = 0; j < num_scores - i - 1; ++j) {
            if (scores[j] < scores[j + 1]) {
                std::swap(scores[j], scores[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;                               // Se non ci sono stati scambi, l'array è già ordinato
    }
}

void Leaderboard::showLeaderboard() {
    clear();  

    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    mvprintw(1, max_x / 2 - 6, "Classifica");

    int start_y = max_y / 2 - (num_scores / 2);              // Centro verticale della classifica
    for (int i = 0; i < num_scores; ++i) {
        mvprintw(start_y + i, max_x / 2 - 10, "%d. %d", i + 1, scores[i]);
    }

    mvprintw(start_y + 25, max_x / 2 - 10, "Premi M per tornare al menu principale");

    refresh();

    int ch;
    while ((ch = getch()) != 'm') {                       // Aspetta l'input
        
    }

    Menu menu;                                            // Torna al menu
    menu.showMainMenu();
}
