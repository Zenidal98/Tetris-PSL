#ifndef GAME_HPP
#define GAME_HPP

#include <ncurses.h>
#include <chrono>
#include <fstream>

// Dimensions of the game board
const int WIDTH = 10;
const int HEIGHT = 20;

// Define the shapes of the tetrominoes
const int TETROMINO_ROTATIONS[7][4][4][4] = {
    // I
    {
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }, {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },
    // J
    {
        {
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
        }, {
            {0, 1, 1},
            {0, 1, 0},
            {0, 1, 0}
        }, {
            {0, 0, 0},
            {1, 1, 1},
            {0, 0, 1}
        }, {
            {0, 1, 0},
            {0, 1, 0},
            {1, 1, 0}
        }
    },
    // L
    {
        {
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 1}
        }, {
            {0, 0, 0},
            {1, 1, 1},
            {1, 0, 0}
        }, {
            {1, 1, 0},
            {0, 1, 0},
            {0, 1, 0}
        }
    },
    // O
    {
        {
            {1, 1},
            {1, 1}
        }, {
            {1, 1},
            {1, 1}
        }, {
            {1, 1},
            {1, 1}
        }, {
            {1, 1},
            {1, 1}
        }
    },
    // S
    {
        {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1}
        }, {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1}
        }
    },
    // T
    {
        {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 1},
            {0, 1, 0}
        }, {
            {0, 0, 0},
            {1, 1, 1},
            {0, 1, 0}
        }, {
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 0}
        }
    },
    // Z
    {
        {
            {1, 1, 0},
            {0, 1, 1},
            {0, 0, 0}
        }, {
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 0}
        }, {
            {0, 0, 0},
            {1, 1, 0},
            {0, 1, 1},
        }, {
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 0},
        }
    }
};

enum Direction { LEFT, RIGHT, DOWN };

enum TetrominoType { I, J, L, O, S, T, Z, NumTetrominoTypes }; // For randomizing tetrominoes, last number as control

class Game {
public:
    Game();
    void start();

private:
    void init();
    void draw();
    void input();
    void logic();
    bool checkCollision(int x, int y, const int shape[4][4]);
    void rotateTetromino();
    void mergeTetromino();
    void clearLines();
    void saveScore(int score);  // per la classifica private

    int score;
    int currentX, currentY;
    TetrominoType currentType;
    int board[HEIGHT][WIDTH];
    int currentTetromino[4][4];
    int currentRotation;

    // per aumentare la velocità
    int n = 1;
    int difficulty = 150;

    std::chrono::steady_clock::time_point startTime;
    std::chrono::time_point<std::chrono::steady_clock> pauseStartTime;
    std::chrono::time_point<std::chrono::steady_clock> lastFallTime;  //per non far scendere i blocchi più veloci dopo la pausa
    int elapsedTime;

    bool paused = false;

    enum class GameState{
       Playing,
       GameOver
    };

    GameState state;

};

#endif // TUTILS_HPP
