#include "Game.hpp"
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <algorithm>

Game::Game() 
    : currentTetromino(TetrominoType(rand() % NumTetrominoTypes)),
      score(0), gameOver(false), currentX(WIDTH / 2 - 2), currentY(0),
      difficulty(150), elapsedTime(0), paused(false), state(GameState::Playing) {
    init();
}

void Game::init() {
    srand(static_cast<unsigned>(time(0)));
    std::fill(&board[0][0], &board[0][0] + sizeof(board) / sizeof(int), 0);
    startTime = std::chrono::steady_clock::now();
    lastFallTime = startTime;
    paused = false;
}

void Game::start() {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    while (!gameOver) {
        input();
        if (!paused) {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed = now - lastFallTime;

            if (elapsed.count() >= difficulty / 1000.0) {
                logic();
                lastFallTime = now;
            }
        }
        draw();
    }

    endwin();
    menu.showGameOverScreen();
}

void Game::draw() {
    clear();

    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            if (board[y][x]) {
                mvaddch(y, x, '#');
            }
        }
    }

    auto shape = currentTetromino.getShape();
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if ((*shape)[y][x]) {
                mvaddch(currentY + y, currentX + x, '#');
            }
        }
    }

    mvprintw(0, 0, "Score: %d", score);

    refresh();
}

void Game::input() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (!checkCollision(currentX - 1, currentY, *currentTetromino.getShape())) {
                --currentX;
            }
            break;
        case KEY_RIGHT:
            if (!checkCollision(currentX + 1, currentY, *currentTetromino.getShape())) {
                ++currentX;
            }
            break;
        case KEY_DOWN:
            if (!checkCollision(currentX, currentY + 1, *currentTetromino.getShape())) {
                ++currentY;
            }
            break;
        case ' ':
            rotateTetromino();
            break;
        case 'p':
            paused = !paused;
            if (paused) {
                pauseStartTime = std::chrono::steady_clock::now();
            } else {
                auto now = std::chrono::steady_clock::now();
                elapsedTime += std::chrono::duration_cast<std::chrono::seconds>(now - pauseStartTime).count();
            }
            break;
        case 'q':
            gameOver = true;
            break;
    }
}

void Game::logic() {
    if (!checkCollision(currentX, currentY + 1, *currentTetromino.getShape())) {
        ++currentY;
    } else {
        mergeTetromino();
        clearLines();
        currentTetromino = TetrominoType(rand() % NumTetrominoTypes);
        currentX = WIDTH / 2 - 2;
        currentY = 0;
        if (checkCollision(currentX, currentY, *currentTetromino.getShape())) {
            gameOver = true;
        }
    }
}

bool Game::checkCollision(int x, int y, const int shape[4][4]) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (shape[i][j] && (x + j < 0 || x + j >= WIDTH || y + i >= HEIGHT || board[y + i][x + j])) {
                return true;
            }
        }
    }
    return false;
}

void Game::rotateTetromino() {
    int oldRotation = currentTetromino.getRotation();
    currentTetromino.setRotation((currentTetromino.getRotation() + 1) % 4);
    if (checkCollision(currentX, currentY, *currentTetromino.getShape())) {
        currentTetromino.setRotation(oldRotation);
    }
}

void Game::mergeTetromino() {
    auto shape = currentTetromino.getShape();
    for (int y = 0; y < 4; ++y) {
        for (int x = 0; x < 4; ++x) {
            if ((*shape)[y][x]) {
                board[currentY + y][currentX + x] = 1;
            }
        }
    }
}

void Game::clearLines() {
    for (int y = HEIGHT - 1; y >= 0; --y) {
        bool lineFull = true;
        for (int x = 0; x < WIDTH; ++x) {
            if (!board[y][x]) {
                lineFull = false;
                break;
            }
        }
        if (lineFull) {
            for (int k = y; k > 0; --k) {
                std::copy(board[k - 1], board[k - 1] + WIDTH, board[k]);
            }
            std::fill(board[0], board[0] + WIDTH, 0);
            ++score;
            ++y;
        }
    }
}
