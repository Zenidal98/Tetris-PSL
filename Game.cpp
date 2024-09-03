#include "Game.hpp"
#include "Menu.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <chrono>

Game::Game() : startTime(std::chrono::steady_clock::now()), lastFallTime(std::chrono::steady_clock::now()), elapsedTime(0), 
               paused(false), state(GameState::Playing) {
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

void Game::start() {
    while (state != GameState::GameOver) {
        draw();
        input();
        logic();
    }
  Menu menu;
  menu.showGameOverScreen(score, elapsedTime);
   // endwin();
}

void Game::draw() {
    // Create an off-screen window for the play area with border
    WINDOW *playArea = newwin(HEIGHT + 2, WIDTH * 2 + 2, 0, 0);  // Adjusted window size for the play area with border

    // Draw the border around the play area
    box(playArea, 0, 0);  // Draws a border around the play area

    // Draw the board to the play area window
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x]) {
                wattron(playArea, COLOR_PAIR(board[y][x]));
                mvwprintw(playArea, y + 1, x * 2 + 1, "[]");  // Adjust position for the border
                wattroff(playArea, COLOR_PAIR(board[y][x]));
            }
        }
    }

    // Draw the current tetromino to the play area window
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentTetromino[y][x]) {
                wattron(playArea, COLOR_PAIR(currentType + 1));
                mvwprintw(playArea, currentY + y + 1, (currentX + x) * 2 + 1, "[]");  // Adjust position for the border
                wattroff(playArea, COLOR_PAIR(currentType + 1));
            }
        }
    }

    // Refresh the play area window to display the content and border
    wrefresh(playArea);

    // Free the play area window
    delwin(playArea);

    // Display the score and time in the main screen (stdscr)
    mvprintw(0, WIDTH * 2 + 4, "Punteggio: %d", score);

    // Track and display elapsed time
    if(!paused){
        auto now = std::chrono::steady_clock::now();
        elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
        mvprintw(2, WIDTH * 2 + 4, "Tempo: %d", elapsedTime);
    }
    // Mostra comandi
    mvprintw(4, WIDTH * 2 + 4, "Comandi:");
    mvprintw(6, WIDTH * 2 + 4, "Spazio per ruotare");
    mvprintw(8, WIDTH * 2 + 4, "P per pausa");
    mvprintw(10, WIDTH * 2 + 4, "Freccia giù per piazzare subito il blocco");
    mvprintw(12, WIDTH * 2 + 4, "R per ricominciare");

    refresh();  // Refresh the main screen to show the score and time
}


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
                while (!checkCollision(currentX, currentY + 1, currentTetromino)) currentY++;
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
                mvprintw(14, WIDTH * 2 + 4, "Pausa attiva, fai ripartire il gioco con P");
                refresh();
            }
            else{
                auto pauseEndTime = std::chrono::steady_clock::now();
                startTime += pauseEndTime - pauseStartTime;
                lastFallTime += pauseEndTime - pauseStartTime; // Adjust lastFallTime to maintain consistency
                nodelay(stdscr, TRUE);
                mvprintw(14, WIDTH * 2 + 4, "                                                      ");
                refresh();
            }
            break;
    }

    if(score > 200*n && difficulty >=50){
        difficulty = difficulty - 20;
        n++;
    }
    napms(difficulty);
}

void Game::logic() {
    if(paused)
        return;

    // Control block fall speed
    auto now = std::chrono::steady_clock::now();
    auto elapsedSinceLastFall = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count();

    // Adjust the fall interval as needed
    int fallInterval = difficulty; // Milliseconds between each block fall

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
    int counter = 0;
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
            counter++;
            y++;
        }
    }
    if(counter > 0)
        score += 100 * counter + 50 * (counter-1);
}
