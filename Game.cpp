#include "Game.hpp"

// Constructor for the Game class
Game::Game() 
    : board(), userInterface(), startTime(std::chrono::steady_clock::now()), 
      lastFallTime(std::chrono::steady_clock::now()), elapsedTime(0), 
      paused(false), state(GameState::Playing) {
    init();
}

// Initialize game settings
void Game::init() {
    userInterface.init();  // Initialize user interface
    score = 0;
    gameOver = false;

    // Initialize the board
    board.reset();
    
    // Initialize current tetromino
    currentType = TetrominoType(rand() % NumTetrominoTypes);
    currentRotation = 0;
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            currentTetromino[i][j] = TETROMINO_ROTATIONS[currentType][currentRotation][i][j];
        }
    }
    currentX = WIDTH / 2 - 2;
    currentY = 0;

    startTime = std::chrono::steady_clock::now(); 
    lastFallTime = std::chrono::steady_clock::now();
}

// Start the game loop
void Game::start() {
    while (state != GameState::GameOver) {
        userInterface.draw(board, score, elapsedTime, paused, currentType, currentTetromino, currentX, currentY);
        input();
        logic();
    }
    showGameOverScreen();
}

// Handle user input
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
            if (!paused) {
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
                if (checkCollision(currentX, currentY, currentTetromino)) gameOver = true;
            }
            break;
        case ' ':
            if (!paused) rotateTetromino();
            break;
        case 'p':
            paused = !paused;
            if (paused) {
                pauseStartTime = std::chrono::steady_clock::now();
                nodelay(stdscr, FALSE);
                userInterface.displayPauseMessage();
            } else {
                auto pauseEndTime = std::chrono::steady_clock::now();
                startTime += pauseEndTime - pauseStartTime;
                lastFallTime += pauseEndTime - pauseStartTime;
                nodelay(stdscr, TRUE);
                userInterface.clearPauseMessage();
            }
            break;
    }

    if (score > 200 * n && difficulty >= 50) {
        difficulty = difficulty - 20;
        n++;
    }
    napms(difficulty);
}

// Game logic
void Game::logic() {
    if (paused) return;

    auto now = std::chrono::steady_clock::now();
    auto elapsedSinceLastFall = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastFallTime).count();

    int fallInterval = difficulty;

    if (elapsedSinceLastFall > fallInterval) {
        if (!checkCollision(currentX, currentY + 1, currentTetromino)) {
            currentY++;
        } else {
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
        lastFallTime = now;
    }
    board.clearLines(score);
}

// Check for collision
bool Game::checkCollision(int x, int y, const int shape[4][4]) {
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 4; i++) {
            if (shape[j][i]) {
                int boardX = x + i;
                int boardY = y + j;
                if (boardX < 0 || boardX >= WIDTH || boardY >= HEIGHT || boardY < 0 || board.getCell(boardY, boardX)) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Rotate the tetromino
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

// Merge the current tetromino into the board
void Game::mergeTetromino() {
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (currentTetromino[y][x]) {
                board.setCell(currentY + y, currentX + x, currentType + 1);
            }
        }
    }
}

// Show the game over screen
void Game::showGameOverScreen() {
    userInterface.showGameOverScreen(score, elapsedTime);
    if (state == GameState::Playing) {
        init();
        start();
    }
}

