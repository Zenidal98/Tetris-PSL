#ifndef GAME_HPP
#define GAME_HPP

#include "Tetromino.hpp"
#include "Leaderboard.hpp"
#include "Menu.hpp"
#include <chrono>

const int WIDTH = 10;
const int HEIGHT = 20;

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

    Tetromino currentTetromino;
    int score;
    bool gameOver;
    int currentX, currentY;
    int board[HEIGHT][WIDTH];
    int currentRotation;
    int difficulty;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point pauseStartTime;
    std::chrono::steady_clock::time_point lastFallTime;
    int elapsedTime;
    bool paused;
    Menu menu;
    Leaderboard leaderboard;

    enum class GameState {
        Playing,
        GameOver
    };

    GameState state;
};

#endif // GAME_HPP
