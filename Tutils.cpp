#include "Tutils.hpp"
#include "Grid.hpp"

class Tetromino {
public:
  // Constructor to create a Tetromino with a random shape and initial position
  Tetromino(){
    int shapeIndex = rand() % 7; // Get a random shape from the shapes array
    copy(&shapes[shapeIndex][0][0], &shapes[shapeIndex][0][0] + 16, &shape[0][0]);
    x = 10 / 2 - 2;     // Center the tetromino horizontally (adjust offset as needed)
    y = 0;              // Start at the top
    rotation = 0;       // Initial rotation
  }
  
  static const int shapes[7][4][4];

  // Create a clone of a given Tetromino, now probably obsolete
  Tetromino(const Tetromino& other) {
    copyShape(other.shape, shape);  // Deep copy the shape
    x = other.x;
    y = other.y;
    rotation = other.rotation;
  }
  void Tetromino::moveUp() {
    y--;
  }

  void Tetromino::moveDown() {
    y++;
  }

  void Tetromino::moveRight() {
    x++;
  }

  void Tetromino::moveLeft() {
    x--;
  }

  void rotateTetromino(Tetromino falling_block){
    // ruota il tetromino di 90 gradi aggiornando i valori interni delle matrici,
    // ovviamente aggiornando anche il rotation state. se non dovesse del tutto funzionare,
    // (andra integrato alle collisoni) mi tocchera definire a mano tutti gli stadi di rotazione
   /**  if (falling_block.shape.size() != 4 || falling_block.shape[0].size() != 4){
        return; // per le forme insolite, non so se serve
    }**/

    // "ombra" temporanea per cambiare la forma 
    int newShape[4][4];
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            newShape[i][j] = falling_block.shape[j][3-i];
        }
    }
    int tmp[4][4];
    copyShape(falling_block.shape, tmp);              //salva forma pre rot
    copyShape(newShape, falling_block.shape);
    if(!isColliding(falling_block, g, 0, 0)){         // check collisione post rot
      falling_block.rotation = (falling_block.rotation + 1) % 4;
      return;
    }else{ 
      copyShape(tmp, falling_block.shape);           //revert forma se collide
      return;
    }
    
  }

  // Function to check for collision (dx and dy to check further positions while moving)
  bool isColliding(const Tetromino block, const int grid[20][10], int dx = 0, int dy = 0) {
  // Check for collisions with the grid and potential new position
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (block.shape[i][j] == 1 &&
          (block.y + i + dy < 0 ||  // Check if outside top bound
           block.y + i + dy >= 20 || // Check if outside bottom bound
           block.x + j + dx < 0 ||  // Check if outside left bound
           block.x + j + dx >= 10 || // Check if outside right bound
           grid[block.y + i + dy][block.x + j + dx] == 1)) {
         return true;
       }
     }
    }
    return false;
  }

  void display(WINDOW *win){
    wattron(win, COLOR_PAIR(rand()%256));
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        
      }
    }
  }
private:
  // Tetromino shape
  int shape[4][4];

  // Current position (x, y)
  int x;
  int y;

  // Rotation state
  int rotation;

  void copyShape(const int src[4][4], int dest[4][4]) {
    std::copy(&src[0][0], &src[0][0] + 16, &dest[0][0]);
  }
  
};


// Predefined tetromino shapes (replace with actual definitions from Tutils.hpp)
   const int Tetromino::shapes[7][4][4] = {
    
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


