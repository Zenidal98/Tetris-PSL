#include "Main.hpp"
#include "Game.hpp"

void Menu::showGameMenu() {

    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    int scelta = 0; // Variabile per la scelta dell'utente
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);

    while (true) {
        werase(stdscr); // Cancella la finestra principale senza aggiornarla subito

                                     // Calcola la posizione centrale
        int start_y = max_y / 2 - 2; // Riga di partenza per il testo
        int start_x = (max_x - 20) / 2; // Colonna di partenza per il testo, considerando la lunghezza massima dell'opzione

                                                              // Mostra il menu
        mvprintw(start_y, start_x, "Benvenuto nel Tetris!");
        mvprintw(start_y + 2, start_x, "Nuova Partita");
        mvprintw(start_y + 3, start_x, "Classifica");
        mvprintw(start_y + 4, start_x, "Esci");

                                                             // Evidenzia la scelta corrente con una freccia
        if (scelta == 0) mvprintw(start_y + 2, start_x - 2, ">");
        else if (scelta == 1) mvprintw(start_y + 3, start_x - 2, ">");
        else if (scelta == 2) mvprintw(start_y + 4, start_x - 2, ">");

        wnoutrefresh(stdscr);                               // Aggiorna la finestra virtuale senza aggiornarla sullo schermo
        doupdate();                                         // Aggiorna effettivamente lo schermo con le modifiche fatte

        int ch = getch();

        switch (ch) {
            case KEY_UP:
                scelta = (scelta - 1 + 3) % 3; // Muovi verso l'alto (3 opzioni)
                break;
            case KEY_DOWN:
                scelta = (scelta + 1) % 3; // Muovi verso il basso (3 opzioni)
                break;
            case '\n': // Invio
                if (scelta == 0) {
                    clear();
                    endwin(); // Ripristina il terminale prima di cambiare
                    game->state = GameState::Playing;
                    game->init();
                    game->start(); // Avvia il gioco
                    return;
                }   else if (scelta == 1) {
                    endwin(); // Ripristina il terminale prima di mostrare la classifica
                    showLeaderboard(); // Mostra la classifica
                    return;
                }   else if (scelta == 2) {
                    endwin(); // Ripristina il terminale prima di uscire
                    exit(0);
                }
                break;
        }
    }
}

void Menu::showGameOverScreen() {
    game->clear(); // Pulisce la schermata

    // Calcola il punteggio totale
    auto now = std::chrono::steady_clock::now();
    game->elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - game->startTime).count();
    int totalScore = game->score + (game->elapsedTime / 2);

    game->saveScore(totalScore);

    // Mostra il messaggio di game over, il punteggio, e le possibilità
    mvprintw(LINES / 2 - 2, COLS / 2 - 10, "Game Over");
    mvprintw(LINES / 2, COLS / 2 - 10, "Score: %d", totalScore);
    mvprintw(LINES / 2 + 2, COLS / 2 - 10, "Press 'q' to quit");
    mvprintw(LINES / 2 + 4, COLS / 2 - 10, "Press 'c' to play again");
    mvprintw(LINES / 2 + 6, COLS / 2 - 10, "Press 'm' to return to main menu");

    refresh();
    int ch;
    while ((ch = getch()) != 'q' && ch != 'c' && ch != 'm') {
        // Aspetta input
    }

    if (ch == 'c') {
        // Rinizializza e inizia una nuova partita
        game->init();
        game->state = GameState::Playing;
        game->start(); // Avvia il gioco
    } else if (ch == 'm') {
        // Torna al menu principale
        game->state = GameState::GameOver; // Per uscire dal loop del gioco
        game->clear();
        showGameMenu();
    } else if (ch == 'q') {
        endwin(); // Chiude la finestra ncurses
        exit(0); // Esce dal programma
    }
}

void Menu::showLeaderboard() {
    clear();
    std::ifstream file("leaderboard.txt");
    std::vector<int> scores;

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Assicurati che la linea non sia vuota e che possa essere convertita in un intero
            if (!line.empty() && std::all_of(line.begin(), line.end(), ::isdigit)) {
                int score = std::stoi(line);
                scores.push_back(score);
            }
        }
        file.close();
    }

    // Ordina i punteggi in ordine decrescente
    std::sort(scores.begin(), scores.end(), std::greater<int>());

    // Stampa la classifica
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    mvprintw(0, 0, "Premi 'q' per tornare al menu principale");

    int start_y = max_y / 2 - (scores.size() / 2); // Centro verticale della classifica
    for (size_t i = 0; i < scores.size(); ++i) {
        mvprintw(start_y + i, max_x / 2 - 10, "%d", scores[i]);
    }
    refresh();

    int ch;
    while ((ch = getch()) != 'q') {
        // Attende che l'utente prema 'q'
    }
    showGameMenu();
}
