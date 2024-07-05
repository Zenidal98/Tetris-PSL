#include "Tutils.hpp"
#include <cstdlib> // For rand()

// Define the static shapes array
const int Tetromino::shapes[7][4][4] = {
    // Tetromino shapes (as previously defined)
    {{0,0,0,0}, {1,1,1,1}, {0,0,0,0}, {0,0,0,0}}, // I
    {{0,0,0,0}, {0,1,1,1}, {0,0,1,0}, {0,0,0,0}}, // T
    {{0,0,0,0}, {0,1,1,0}, {0,1,1,0}, {0,0,0,0}}, // O
    {{0,0,0,0}, {0,0,1,1}, {0,1,1,0}, {0,0,0,0}}, // S
    {{0,0,0,0}, {0,1,1,0}, {0,0,1,1}, {0,0,0,0}}, // Z
    {{0,0,0,0}, {1,0,0,0}, {1,1,1,0}, {0,0,0,0}}, // J
    {{0,0,0,0}, {0,0,0,1}, {0,1,1,1}, {0,0,0,0}}  // L
};

// Constructor to create a Tetromino with a random shape and initial position
Tetromino::Tetromino() {
    int shapeIndex = rand() % 7; // Get a random shape from the shapes array
    copy(&shapes[shapeIndex][0][0], &shapes[shapeIndex][0][0] + 16, &shape[0][0]);
    x = 10 / 2 - 2;     // Center the tetromino horizontally (adjust offset as needed)
    y = 0;              // Start at the top
    rotation = 0;       // Initial rotation
}

// Create a clone of a given Tetromino
Tetromino::Tetromino(const Tetromino& other) {
    copyShape(other.shape, shape);  // Deep copy the shape
    x = other.x;
    y = other.y;
    rotation = other.rotation;
}

// Move the tetromino down
void Tetromino::moveDown() {
    y++;
}

// Move the tetromino right
void Tetromino::moveRight() {
    x++;
}

// Move the tetromino left
void Tetromino::moveLeft() {
    x--;
}

// Rotate the tetromino 90 degrees
void Tetromino::rotateTetromino(Tetromino falling_block) {
    int newShape[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            newShape[i][j] = falling_block.shape[j][3 - i];
        }
    }
    int tmp[4][4];
    copyShape(falling_block.shape, tmp); // Save pre-rotation shape
    copyShape(newShape, falling_block.shape);
    if (falling_block.isColliding(0,0)==true) { // Check collision post-rotation
        falling_block.rotation = (falling_block.rotation + 1) % 4;
    } else {
        copyShape(tmp, falling_block.shape); // Revert shape if it collides
    }
}

// Check for collision
bool Tetromino::isColliding(int dx, int dy) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                int newX = x + j + dx;
                int newY = y + i + dy;
                if (newX < 0 || newX >= 10 || newY < 0 || newY >= 20 || g[newY][newX] == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Display the tetromino
void Tetromino::display(WINDOW *win, int col) {
    wattron(win, col);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                mvwaddch(win, y + i, x + j, 'X');
            }
        }
    }
    wattroff(win, col);
}

// Write the tetromino values to the grid
void Tetromino::writeToGrid(int grid[20][10]) const {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (shape[i][j] == 1) {
                grid[y + i][x + j] = 1;
            }
        }
    }
}

// Helper function to copy shapes
void Tetromino::copyShape(const int src[4][4], int dest[4][4]) {
    std::copy(&src[0][0], &src[0][0] + 16, &dest[0][0]);
}
