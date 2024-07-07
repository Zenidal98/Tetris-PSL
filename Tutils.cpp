#include "Tutils.hpp"
#include "cstdlib"
#include "ctime"

Game::Game() {
    init();
}

Game::~Game() {
    endwin();
}

void Game::init() {
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
    board = vector<vector<int>>(HEIGHT, vector<int>(WIDTH, 0));
    currentType = static_cast<TetrominoType>(rand() % NumTetrominoTypes);
    currentRotation = 0;
    currentTetromino = TETROMINO_ROTATIONS[currentType][currentRotation];
    currentX = WIDTH / 2 - currentTetromino[0].size() / 2;
    currentY = 0;
}

void Game::start() {
    while (!gameOver) {
        draw();
        input();
        logic();
    }
}

void Game::draw() {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x]) {  
              mvprintw(y, x*2, "[]"); // x*2 makes "[]" more "square"
            }
        }
    }

    for (int y = 0; y < currentTetromino.size(); y++) {
        for (int x = 0; x < currentTetromino[y].size(); x++) {
            if (currentTetromino[y][x]) {
                mvprintw(currentY + y, (currentX + x)*2, "[]");
            }
        }
    }

    mvprintw(0, WIDTH * 2 + 2, "Score: %d", score);
    refresh();
}

void Game::input() {
    int ch = getch();
    switch (ch) {
        case KEY_LEFT:
            if (!checkCollision(currentX - 1, currentY, currentTetromino)) currentX--;
            break;
        case KEY_RIGHT:
            if (!checkCollision(currentX + 1, currentY, currentTetromino)) currentX++;
            break;
        case KEY_DOWN:
            if (!checkCollision(currentX, currentY + 1, currentTetromino)) currentY++;
            else {
                mergeTetromino();
                currentType = static_cast<TetrominoType>(rand() % NumTetrominoTypes);
                currentTetromino = TETROMINO_ROTATIONS[currentType][currentRotation];
                currentX = WIDTH / 2 - currentTetromino[0].size() / 2;
                currentY = 0;
                if (checkCollision(currentX, currentY, currentTetromino)) gameOver = true;
            }
            break;
        case 'q':
            gameOver = true;
            break;
        case ' ':
            rotateTetromino();
            break;
    }
}

void Game::logic() {
    if (!checkCollision(currentX, currentY + 1, currentTetromino)) {
        currentY++;
    } else {
        mergeTetromino();
        currentType = static_cast<TetrominoType>(rand() % NumTetrominoTypes);
        currentTetromino = TETROMINO_ROTATIONS[currentType][currentRotation];
        currentX = WIDTH / 2 - currentTetromino[0].size() / 2;
        currentY = 0;
        if (checkCollision(currentX, currentY, currentTetromino)) gameOver = true;
    }
    clearLines();
}

bool Game::checkCollision(int x, int y, const vector<vector<int>>& shape) {
    for (int j = 0; j < shape.size(); j++) {
        for (int i = 0; i < shape[j].size(); i++) {
            if (shape[j][i]) {
                // Check for board boundaries and collisions
                if (x + i < 0 || x + i >= WIDTH || y + j < 0 || y + j >= HEIGHT || board[y + j][x + i]) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::rotateTetromino() {
    int nextRotation = (currentRotation + 1) % 4;
    const vector<vector<int>>& rotated = TETROMINO_ROTATIONS[currentType][nextRotation];

    if (!checkCollision(currentX, currentY, rotated)) {
        currentTetromino = rotated;
        currentRotation = nextRotation;
    }
}


void Game::mergeTetromino() {
    for (int y = 0; y < currentTetromino.size(); y++) {
        for (int x = 0; x < currentTetromino[y].size(); x++) {
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
            board.erase(board.begin() + y);
            board.insert(board.begin(), vector<int>(WIDTH, 0));
            score += 100;
            y++;
        }
    }
}

