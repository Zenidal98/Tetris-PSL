#include "Grid.hpp"

// Define the static member
int Grid::grid[20][10];

// Initialize the reference to the static grid array
int (&g)[20][10] = Grid::grid;

// Constructor to initialize the grid
Grid::Grid() {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 10; j++) {
            grid[i][j] = 0;
        }
    }
}
