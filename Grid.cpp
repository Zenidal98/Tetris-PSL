#include "Grid.hpp"

class Grid {
public:
    static int grid[20][10];

    Grid() {
        for (int i = 0; i < 20; i++) {
            for (int j = 0; j < 10; j++) {
                grid[i][j] = 0;
            }
        }
    }
};



