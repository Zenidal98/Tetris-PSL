#ifndef GRID_HPP
#define GRID_HPP

class Grid {
public:

    static int grid[20][10];

    Grid();
    
};

int Grid::grid[20][10];
Grid G;
int (&g)[20][10] = Grid::grid;          // usa g come reference a Grid::grid
#endif // GRID_HPP
