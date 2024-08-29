#include "Tutils.hpp"
#include <cstdlib>
#include <ctime>

Game::Game() : startTime(std::chrono::steady_clock::now()), lastFallTime(std::chrono::steady_clock::now()), elapsedTime(0), paused(false), state(GameState::Playing) {
    init();
}


void Game::init() {
    clear(); // need in case of previous gameover and previous match
    refresh();
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100);

    // Define tetromino color pairs
    init_pair(I + 1, COLOR_CYAN, COLOR_BLACK);
    init_pair(J + 1, COLOR_BLUE, COLOR_BLACK);
    init_pair(L + 1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(O + 1, COLOR_WHITE, COLOR_BLACK);
    init_pair(S + 1, COLOR_GREEN, COLOR_BLACK);
    init_pair(T + 1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(Z + 1, COLOR_RED, COLOR_BLACK);

    srand(time(NULL));
    score = 0;
    gameOver = false;
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            board[i][j] = 0;
        }
    }
    currentType = TetrominoType(rand() % NumTetrominoTypes);
    currentRotation = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            currentTetromino[i][j] = TETROMINO_ROTATIONS[currentType][currentRotation][i][j];
        }
    }
    currentX = WIDTH / 2 - 2;
    currentY = 0;

    startTime = std::chrono::steady_clock::now(); //important so the time is resetted every match
    lastFallTime = std::chrono::steady_clock::now();
}

void Game::showGameOverScreen() {
    clear(); // Pulisce la schermata

    // Calcola il punteggio totale
    auto now = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    int totalScore = score + (elapsedTime / 2);

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
        init();
        state = GameState::Playing;
        start(); // Avvia il gioco
    } else if (ch == 'm') {
        // Torna al menu principale
        state = GameState::GameOver; // Per uscire dal loop del gioco
        clear();
        showGameMenu();
    } else if (ch == 'q') {
        endwin(); // Chiude la finestra ncurses
        exit(0); // Esce dal programma
    }
}

void Game::showGameMenu() {

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
                    state = GameState::Playing;
                    init();
                    start(); // Avvia il gioco
                    return;
                } /*else if (scelta == 1) {
                    endwin(); // Ripristina il terminale prima di mostrare la classifica
                    showLeaderboard(); // Mostra la classifica
                    return;
                }*/ else if (scelta == 2) {
                    endwin(); // Ripristina il terminale prima di uscire
                    exit(0);
                }
                break;
        }
    }
}

void Game::start() {
    while (state != GameState::GameOver) {
        draw();
        input();
        logic();
    }
   showGameOverScreen();
   // endwin();
}

void Game::draw() {
    // Create an off-screen window
    WINDOW *offscreen = newwin(HEIGHT, WIDTH * 2 + 20, 0, 0);

    // Draw the board to the off-screen window
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x]) {
                wattron(offscreen, COLOR_PAIR(board[y][x]));
                mvwprintw(offscreen, y, x * 2, "[]"); // x*2 makes "[]" more "square"
                wattroff(offscreen, COLOR_PAIR(board[y][x]));
            }
        }
    }

    // Draw the current tetromino to the off-screen window
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentTetromino[y][x]) {
                wattron(offscreen, COLOR_PAIR(currentType + 1));
                mvwprintw(offscreen, currentY + y, (currentX + x) * 2, "[]");
                wattroff(offscreen, COLOR_PAIR(currentType + 1));
            }
        }
    }

    // Draw the score to the off-screen window
    mvwprintw(offscreen, 0, WIDTH * 2 + 2, "Score: %d", score);

    // Track elapsed time
    auto now = std::chrono::steady_clock::now();
    elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    mvwprintw(offscreen, 2, WIDTH * 2 + 2, "Time: %d", elapsedTime);

    // Copy the off-screen window to the main screen
    overwrite(offscreen, stdscr);
    refresh();

    // Free the off-screen window
    delwin(offscreen);
}

/*void Game::draw() {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x]) {
                attron(COLOR_PAIR(board[y][x]));
                mvprintw(y, x * 2, "[]"); // x*2 makes "[]" more "square"
                attroff(COLOR_PAIR(board[y][x]));
            }
        }
    }

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentTetromino[y][x]) {
                attron(COLOR_PAIR(currentType + 1));
                mvprintw(currentY + y, (currentX + x) * 2, "[]");
                attroff(COLOR_PAIR(currentType + 1));
            }
        }
    }

    mvprintw(0, WIDTH * 2 + 2, "Score: %d", score);
    refresh();
}*/

void Game::input() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (!paused && !checkCollision(currentX - 1, currentY, currentTetromino)) currentX--;
            break;
        case KEY_RIGHT:
            if (!paused && !checkCollision(currentX + 1, currentY, currentTetromino)) currentX++;
            break;
        case KEY_DOWN:
            if(!paused){
                if (!checkCollision(currentX, currentY + 1, currentTetromino)) currentY++;
                else {
                    mergeTetromino();
                    currentType = TetrominoType(rand() % NumTetrominoTypes);
                    currentRotation = 0;
                    for (int i = 0; i < 4; ++i) {
                        for (int j = 0; j < 4; ++j) {
                            currentTetromino[i][j] = TETROMINO_ROTATIONS[currentType][currentRotation][i][j];
                        }
                    }
                    currentX = WIDTH / 2 - 2;
                    currentY = 0;
                    if (checkCollision(currentX, currentY, currentTetromino)) gameOver = true;
                }
            }
            break;
        case ' ':
            if(!paused)
                rotateTetromino();
            break;
        case 'r':
            Game::init();
            Game::start();
            break;
        case 'p':
            paused = !paused;
            if(paused){
                pauseStartTime = std::chrono::steady_clock::now();
                nodelay(stdscr, FALSE);
                mvprintw(3, WIDTH * 2 + 2, "Paused");
                refresh();
            }
            else{
                auto pauseEndTime = std::chrono::steady_clock::now();
                startTime += pauseEndTime - pauseStartTime;
                lastFallTime += pauseEndTime - pauseStartTime; // Adjust lastFallTime to maintain consistency
                nodelay(stdscr, TRUE);
                mvprintw(3, WIDTH * 2 + 2, "      ");
                refresh();
            }
            break;
    }
    napms(100);
}

void Game::logic() {
    if(paused)
        return;

    // Control block fall speed
    auto now = std::chrono::steady_clock::now();
    auto elapsedSinceLastFall = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count();

    // Adjust the fall interval as needed
    const int fallInterval = 150; // Milliseconds between each block fall

    if (elapsedSinceLastFall > fallInterval) {
        if (!checkCollision(currentX, currentY + 1, currentTetromino)) {
            currentY++;
        } else
                {
            mergeTetromino();

            currentType = TetrominoType(rand() % NumTetrominoTypes);

            currentRotation = 0;

            for (int i = 0; i < 4; ++i) {

                for (int j = 0; j < 4; ++j) {

                    currentTetromino[i][j] = TETROMINO_ROTATIONS[currentType][currentRotation][i][j];
                }

            }

            currentX = WIDTH / 2 - 2;
            currentY = 0;

            if (checkCollision(currentX, currentY, currentTetromino)) {
                state = GameState::GameOver;
            }

        }
        lastFallTime = now;     //update lastFallTime
    }
    clearLines();

}

bool Game::checkCollision(int x, int y, const int shape[4][4]) {
    // Iterate over the shape of the tetromino
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            // Check if the cell in the shape is filled
            if (shape[j][i]) {
                // Calculate board coordinates
                int boardX = x + i;
                int boardY = y + j;

                // Check boundaries and collision with filled cells on the board
                if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT || boardY < 0 || board[boardY][boardX]) {
                    return true;  // Collision detected
                }
            }
        }
    }
    return false;  // No collision detected
}

void Game::rotateTetromino() {
    int nextRotation = (currentRotation + 1) % 4;
    const int (*rotated)[4] = TETROMINO_ROTATIONS[currentType][nextRotation];

    if (!checkCollision(currentX, currentY, rotated)) {
        currentRotation = nextRotation;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                currentTetromino[i][j] = rotated[i][j];
            }
        }
    }
}

void Game::mergeTetromino() {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentTetromino[y][x]) {
                board[currentY + y][currentX + x] = currentType + 1;
            }
        }
    }
}

void Game::clearLines() {
    for (int y = HEIGHT - 1; y >= 0; y--) {
        bool fullLine = true;
        for (int x = 0; x < WIDTH; x++) {
            if (!board[y][x]) {
                fullLine = false;
                break;
            }
        }
        if (fullLine) {
            for (int i = y; i > 0; --i) {
                for (int x = 0; x < WIDTH; ++x) {
                    board[i][x] = board[i - 1][x];
                }
            }
            score += 100;
            y++;
        }
    }
}
