#include "Tutils.hpp"
#include "cstdlib"
#include "ctime"

Game::Game() {
    init();
}

Game::~Game() {
    endwin();
}
 //initializza ncurses e la board
void Game::init() {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    timeout(100);

    // definisce le coppie tetramino colore
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
    currentTetromino = TETROMINOES[currentType];
    currentX = WIDTH / 2 - currentTetromino[0].size() / 2;
    currentY = 0;
}

//parte il loop del gioco
void Game::start() {
    while (!gameOver) {
        draw();
        input();
        logic();
    }
}

//printa a schermo i blocchi
void Game::draw() {
    clear();
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (board[y][x]) {
                mvprintw(y, x*2, "[]");     // il *2 rende [] più "quadrato"
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

    mvprintw(0, WIDTH * 2 + 2,"Score: %d", score);
    refresh();
}

//handler dei comandi di movimento e rotazione
void Game::input(){
    int ch = getch();
    switch(ch) {
        case KEY_LEFT:
            if (!checkCollision(currentX - 1, currentY, currentTetromino)) currentX--;
            break;
        case KEY_RIGHT:
            if (!checkCollision(currentX + 1, currentY, currentTetromino)) currentX++;
            break;
        case KEY_DOWN:
            if(!checkCollision(currentX, currentY + 1, currentTetromino)) currentY--;
            else{
                mergeTetromino();     //attacca al "fondo"
                currentTetromino = TETROMINOES[rand() % TETROMINOES.size()]; //istanzia nuovo blocco in cima
                currentX = WIDTH / 2 - currentTetromino[0].size() / 2;
                currentY = 0;
                if(checkCollision(currentX, currentY, currentTetromino)) gameOver = true;
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

//handler per merge causati da "gravità" e pulizia righe
void Game::logic(){
    if (!checkCollision(currentX, currentY + 1, currentTetromino)) {
        currentY++;
    } else {
        mergeTetromino();
        currentType = static_cast<TetrominoType>(rand() % NumTetrominoTypes);
        currentTetromino = TETROMINOES[currentType];
        currentX = WIDTH / 2 - currentTetromino[0].size() / 2;
        currentY = 0;
        if (checkCollision(currentX, currentY, currentTetromino)) gameOver = true;
    }
    clearLines();
}

//controllo delle collisioni con la board
bool Game::checkCollision(int x, int y, const vector<vector<int>>& shape) {
    for (int j = 0; j < shape.size(); j++) {
        for (int i = 0; i < shape[j].size(); i++) {
            if (shape[j][i]) {
                if (x + i < 0 || x + i >= WIDTH || y + j >= HEIGHT || board[y + j][x + i]) return true;
            }
        }
    }
    return false;
}


void Game::rotateTetromino() {
    vector<vector<int>> rotated; // get rotated, idiot
    for (int x = 0; x < currentTetromino[0].size(); x++) {
        vector<int> newRow;
        for (int y = currentTetromino.size() - 1; y >= 0; y--) {
            newRow.push_back(currentTetromino[y][x]);
        }
        rotated.push_back(newRow);
    }
    if (!checkCollision(currentX, currentY, rotated) &&
        currentX + rotated[0].size() <= WIDTH &&           //collisioni create ruotando contro i bordi della board
        currentY + rotated.size() <= HEIGHT) {            //
        currentTetromino = rotated;
    }
}

// attacca il tetramino alla board
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
            board.erase(board.begin() + y);                 //cancella la fullLine (vector riattacca le righe sopra e sotto)
            board.insert(board.begin(), vector<int>(WIDTH, 0)); //riga vuota in cima
            score += 100;    //placeholder for the score system
            y++;
        }
    }
}