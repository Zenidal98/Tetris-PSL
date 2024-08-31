#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include <array>

enum TetrominoType { I, J, L, O, S, T, Z, NumTetrominoTypes };

class Tetromino {
public:
    Tetromino(TetrominoType type);
    void rotate();
    const int (*getShape() const)[4][4];
    TetrominoType getType() const;
    int getRotation() const;
    void setRotation(int rotation);

private:
    static const int TETROMINO_ROTATIONS[7][4][4][4];
    TetrominoType type;
    int rotation;
    int shape[4][4];
    void updateShape();
};

#endif // TETROMINO_HPP
