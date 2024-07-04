#ifndef TUTILS_HPP
#define TUTILS_HPP

#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

class Tetromino {
public:
  // Constructor to create a Tetromino with a random shape and initial position
  Tetromino();

  // Create a clone of a given Tetromino
  Tetromino(const Tetromino& other);

  // Move the tetromino in different directions
  void moveUp();
  void moveDown();
  void moveRight();
  void moveLeft();

  // Rotate the tetromino 90 degrees
  void rotateTetromino(Tetromino falling_block);

  // Check for collision
  bool isColliding(const Tetromino& block, const std::vector<std::vector<int>>& grid, int dx = 0, int dy = 0);

  // Define the static shapes array
  static const int shapes[7][4][4];

private:
  // Tetromino shape
  int shape[4][4];

  // Current position (x, y)
  int x;
  int y;

  // Rotation state
  int rotation;

  // Helper function to copy shapes
  void copyShape(const int src[4][4], int dest[4][4]);

  // Accessors
  std::vector<std::vector<int>> getShape() const;
  int getX() const;
  int getY() const;
  int getRotation() const;
};

#endif // TUTILS_HPP
