#ifndef TUTILS_HPP
#define TUTILS_HPP

// Include ncurses for potential future use (if needed for drawing)
#include <ncurses.h>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int width = 10;
const int height = 20;

// Structure to represent a tetromino
struct Tetromino {
    vector<vector<int>> shape;  // Stores the block positions of the tetromino
    int rotation = 0;           // Current rotation state (0-3)
    int x = 0;                  // X-coordinate of the tetromino
    int y = 0;                  // Y-coordinate of the tetromino
};

// Define all seven tetrominos using the Tetromino structure
extern const vector<Tetromino> tetrominoes;  // Defined outside the header for efficiency

// Function to check for collisions with existing blocks and walls
bool isColliding(const Tetromino& tetromino, const vector<vector<int>>& grid);

#endif // TUTILS_HPP
