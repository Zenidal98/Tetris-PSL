// codice in parte ai,  da usare COME REFERENCE

#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Tutils.hpp"
using namespace std;

// ... (Tetromino structure and definitions as before)

// Function to draw the game grid and tetromino
void drawGrid(const vector<vector<int>>& grid, const Tetromino& tetromino) {
  // Use ncurses functions to draw the grid borders and cells
  // ... (Implement logic to draw grid lines and cells based on grid and tetromino)
}

int main() {
  // Initialize ncurses
  initscr();
  noecho();
  curs_set(FALSE);

  // Define game variables
  const int width = 10;
  const int height = 20;
  vector<vector<int>> grid(height, vector<int>(width, 0));  // Initialize empty grid
  Tetromino currentTetromino = tetrominoes[rand() % tetrominoes.size()];  // Random starting tetromino
  int currentX = width / 2 - 2;  // Center the starting tetromino horizontally (adjust offset as needed)
  int currentY = 0;
  int score = 0;

  // Game loop
  while (true) {
    // Handle user input
    int ch = getch();
    switch (ch) {
      case KEY_LEFT:
        // Check if left movement is possible
        if (currentX > 0 && !isCollision(currentTetromino, grid, { -1, 0 })) {
          currentX--;
        }
        break;
      case KEY_RIGHT:
        // Check if right movement is possible
        if (currentX < width - tetrominoes[currentTetromino.rotation % 4][0].size() && // Adjust based on tetromino width
            !isCollision(currentTetromino, grid, { 1, 0 })) {
          currentX++;
        }
        break;
      case KEY_DOWN:
        // Check if downward movement is possible (soft drop)
        if (currentY < height - tetrominoes[currentTetromino.rotation % 4].size() - 1 && // Adjust based on tetromino height
            !isCollision(currentTetromino, grid, { 0, 1 })) {
          currentY++;
        } else {
          // Handle collision (place tetromino and check for line clears)
          // ... (Implement logic to place the tetromino on the grid and check for completed lines)
        }
        break;
      case KEY_UP:
        // Attempt rotation with wall kicks
        for (int i = 0; i < 4; ++i) { // Try 4 wall kicks
          if (tryWallKick(currentTetromino, grid, i) && !isCollision(currentTetromino, grid)) {
            break; // Rotation successful
          }
        }
        break;
    }

    // Update game logic (gravity, line clearing, etc.)
    // ... (Implement logic for automatic downward movement, line clearing, score updates, etc.)

    // Clear screen and redraw grid and tetromino
    clear();
    drawGrid(grid, currentTetromino);
    refresh();

    // Delay for smooth movement
    napms(100); // Adjust delay for desired speed
  }

  // End game cleanup (optional)
  endwin();
  return 0;
}
