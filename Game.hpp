#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "UserInterface.hpp"
#include <chrono>

enum class GameState {
    Playing,
    Paused,
    GameOver
};

class Game {
public:
    Game();
    void start();
    
private:
    void init();
    void input();
    void logic();
    bool checkCollision(int x, int y, const int shape[4][4]);
    void rotateTetromino();
    void mergeTetromino();
    void showGameOverScreen();

    Board board;
    UserInterface userInterface;
    
    GameState state;
    int score;
    bool gameOver;
    bool paused;
    int currentType;
    int currentRotation;
    int currentTetromino[4][4];
    int currentX;
    int currentY;
    
    int difficulty;
    int n;
    std::chrono::steady_clock::time_point startTime;
    std::chrono::steady_clock::time_point lastFallTime;
    std::chrono::steady_clock::time_point pauseStartTime;
    int elapsedTime;
};

#endif // GAME_HPP

