#include "Tutils.hpp"
#include <cstdlib>
using namespace std;


class Tetromino {
public:
  // Different tetromino shapes represented as 2D vectors
  static const vector<vector<int>> shapes[7];

  // Constructor to create a Tetromino with a random shape and initial position
  Tetromino() {
    shape = shapes[rand() % 7]; // Get a random shape from the shapes array
    x = width / 2 - 2; // Center the tetromino horizontally (adjust offset as needed)
    y = 0;              // Start at the top
    rotation = 0;        // Initial rotation
  }

  // Create a clone of a given Tetromino, now probably obsolete
  Tetromino(const Tetromino& other) {
    shape = other.shape;  // Deep copy the shape
    x = other.x;
    y = other.y;
    rotation = other.rotation;
  }

  // Accessors
  const vector<vector<int>>& getShape() const { return shape; }
  int getX() const { return x; }
  int getY() const { return y; }
  int getRotation() const { return rotation; }

private:
  // Tetromino shape
  vector<vector<int>> shape;

  // Current position (x, y)
  int x;
  int y;

  // Rotation state
  int rotation;

  // Predefined tetromino shapes (replace with actual definitions from Tutils.hpp)
const vector<vector<int>> Tetromino::shapes[7] = {
    
    // tetramino "I"
    {{0,0,0,0},
     {1,1,1,1},
     {0,0,0,0},
     {0,0,0,0}},
        
    // tetramino "T"
    {{0,0,0,0},
     {0,1,1,1},
     {0,0,1,0},
     {0,0,0,0}},
           
    // Tetromino "O"
    {{0,0,0,0},
     {0,1,1,0},
     {0,1,1,0},
     {0,0,0,0}},
        
    // Tetromino "S"
    {{0,0,0,0},
     {0,0,1,1},
     {0,1,1,0},
     {0,0,0,0}},
    
    // Tetromino "Z"
    {{0,0,0,0},
     {0,1,1,0},
     {0,0,1,1},
     {0,0,0,0}},
    
    // Tetromino "J"
    {{0,0,0,0},
     {1,0,0,0},
     {1,1,1,0},
     {0,0,0,0}},
    
    // Tetromino "L"
    {{0,0,0,0},
     {0,0,0,1},
     {0,1,1,1},
     {0,0,0,0}},
    
};

void rotateTetromino(Tetromino& falling_block){
    // ruota il tetromino di 90 gradi aggiornando i valori interni delle matrici,
    // ovviamente aggiornando anche il rotation state. se non dovesse del tutto funzionare,
    // (andra integrato alle collisoni) mi tocchera definire a mano tutti gli stadi di rotazione
    if (falling_block.shape.size() != 4 || falling_block.shape[0].size() != 4){
        return; // per le forme insolite, non so se serve
    }

    // "ombra" temporanea per cambiare la forma 
    vector<vector<int>> newShape(4, vector<int>(4,0));
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            newShape[i][j] = falling_block.shape[j][3-i];
        }
    }
    falling_block.shape = newShape;
    falling_block.rotation = (falling_block.rotation + 1) % 4;
}

// Function to check for collision (dx and dy to check further positions while moving)
bool isColliding(const Tetromino& block, const vector<vector<int>>& grid, int dx = 0, int dy = 0) {
  // Check for collisions with the grid and potential new position
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (block.shape[i][j] == 1 &&
          (block.y + i + dy < 0 ||  // Check if outside top bound
           block.y + i + dy >= height || // Check if outside bottom bound
           block.x + j + dx < 0 ||  // Check if outside left bound
           block.x + j + dx >= width || // Check if outside right bound
           grid[block.y + i + dy][block.x + j + dx] == 1)) {
        return true;
      }
    }
  }
  return false;
}

void Tetromino::moveUp() {
  if (!isColliding(*this, grid, 0, -1)) { // Check for collision if moved up
    y--;
  }
}

void Tetromino::moveDown() {
  if (!isColliding(*this, grid, 0, 1)) { // Check for collision if moved down
    y++;
  }
}

void Tetromino::moveRight() {
  if (!isColliding(*this, grid, 1, 0)) { // Check for collision if moved right
    x++;
  }
}

void Tetromino::moveLeft() {
  if (!isColliding(*this, grid, -1, 0)) { // Check for collision if moved left
    x--;
  }
}

};


