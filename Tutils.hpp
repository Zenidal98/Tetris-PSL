#ifndef TUTILS_HPP
#define TUTILS_HPP

#include <ncurses.h>
#include <vector>

using namespace std;

//dimensions of the game board
const int WIDTH = 10;
const int HEIGHT = 20;

// Define the shapes of the tetrominoes
const std::vector<std::vector<std::vector<int>>> TETROMINOES = {
    {{1, 1, 1, 1}},          // I
    {{1, 1, 1}, {0, 1}},     // J
    {{1, 1, 1}, {1}},        // L
    {{1, 1}, {1, 1}},        // O
    {{0, 1, 1}, {1, 1}},     // S
    {{1, 1, 1}, {0, 1, 0}},  // T
    {{1, 1, 0}, {0, 1, 1}}   // Z
};

enum Direction {LEFT, RIGHT, DOWN};

enum TetrominoType{I, J, L, O, S, T, Z, NumTetrominoTypes}; //per randomizzare i tetromini, ultimo numero come controllo

class Game{
public:
  Game();
  ~Game();
  void start();

private:
  void init();
  void draw();
  void input();
  void logic();
  bool checkCollision(int x, int y, const vector<vector<int>>& shape);
  void rotateTetromino();
  void mergeTetromino();
  void clearLines();

  int score;
  bool gameOver;
  int currentX, currentY;
  TetrominoType currentType;
  vector<vector<int>> board;
  vector<vector<int>> currentTetromino;

};
  
#endif // TUTILS_HPP
