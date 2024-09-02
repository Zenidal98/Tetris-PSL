#include "Tetromino.hpp"

// Define the tetromino shapes
const int Tetromino::TETROMINO_ROTATIONS[7][4][4][4] = {
     {
        {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }, {
            {0, 0, 0, 0},
            {1, 1, 1, 1},
            {0, 0, 0, 0},
            {0, 0, 0, 0}
        }, {
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0},
            {0, 1, 0, 0}
        }
    },
    // J
    {
        {
            {1, 0, 0},
            {1, 1, 1},
            {0, 0, 0}
        }, {
            {0, 1, 1},
            {0, 1, 0},
            {0, 1, 0}
        }, {
            {0, 0, 0},
            {1, 1, 1},
            {0, 0, 1}
        }, {
            {0, 1, 0},
            {0, 1, 0},
            {1, 1, 0}
        }
    },
    // L
    {
        {
            {0, 0, 1},
            {1, 1, 1},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 0},
            {0, 1, 1}
        }, {
            {0, 0, 0},
            {1, 1, 1},
            {1, 0, 0}
        }, {
            {1, 1, 0},
            {0, 1, 0},
            {0, 1, 0}
        }
    },
    // O
    {
        {
            {1, 1},
            {1, 1}
        }, {
            {1, 1},
            {1, 1}
        }, {
            {1, 1},
            {1, 1}
        }, {
            {1, 1},
            {1, 1}
        }
    },
    // S
    {
        {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1}
        }, {
            {0, 1, 1},
            {1, 1, 0},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 1},
            {0, 0, 1}
        }
    },
    // T
    {
        {
            {0, 1, 0},
            {1, 1, 1},
            {0, 0, 0}
        }, {
            {0, 1, 0},
            {0, 1, 1},
            {0, 1, 0}
        }, {
            {0, 0, 0},
            {1, 1, 1},
            {0, 1, 0}
        }, {
            {0, 1, 0},
            {1, 1, 0},
            {0, 1, 0}
        }
    },
    // Z
    {
        {
            {1, 1, 0},
            {0, 1, 1},
            {0, 0, 0}
        }, {
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 0}
        }, {
            {0, 0, 0},
            {1, 1, 0},
            {0, 1, 1},
        }, {
            {0, 0, 1},
            {0, 1, 1},
            {0, 1, 0},
        }
    }
};

Tetromino::Tetromino(TetrominoType type) : type(type), rotation(0) {
    updateShape();
}

void Tetromino::rotate() {
    rotation = (rotation + 1) % 4;
    updateShape();
}

const int (*Tetromino::getShape() const)[4][4] {
    return &shape;
}

TetrominoType Tetromino::getType() const {
    return type;
}

int Tetromino::getRotation() const {
    return rotation;
}

void Tetromino::setRotation(int rotation) {
    this->rotation = rotation;
    updateShape();
}

void Tetromino::updateShape() {
    // Update shape based on type and rotation
    std::copy(&TETROMINO_ROTATIONS[type][rotation][0][0], 
              &TETROMINO_ROTATIONS[type][rotation][0][0] + 16, 
              &shape[0][0]);
}
