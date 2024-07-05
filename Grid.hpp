#ifndef GRID_HPP
#define GRID_HPP

class Grid {
public:
    static int grid[20][10]; // Static member declaration

    Grid();
};

// Reference to the static grid array
extern int (&g)[20][10];

#endif // GRID_HPP
