#include "Tutils.hpp"

// Forme dei tetramini base  ??sara necessario avere tutte la stessa dimensione di griglia? boh
vector<Tetromino> tetrominoes = {
    {    // tetramino "I"
       {{0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0}},
        0
    },    
    {   // tetramino "T"
       {{0,0,0,0},
        {0,1,1,1},
        {0,0,1,0},
        {0,0,0,0}},
        0
    },
    // Tetromino "O"
    {
       {{0,0,0,0},
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0}},
        0
    },
     // Tetromino "S"
    {
       {{0,0,0,0},
        {0,0,1,1},
        {0,1,1,0},
        {0,0,0,0}},
        0
    },
    // Tetromino "Z"
    {
       {{0,0,0,0},
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0}},
        0
    },
    // Tetromino "J"
    {
       {{0,0,0,0},
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0}},
        0
    },
    // Tetromino "L"
    {
       {{0,0,0,0},
        {0,0,0,1},
        {0,1,1,1},
        {0,0,0,0}},
        0
    }
};


void rotateTetromino(Tetromino& falling_block){
    // ruota il tetromino di 90 gradi aggiornando i valori interni delle matrici,
    // ovviamente aggiornando anche il rotation state. se non dovesse del tutto funzionare,
    // (andra integrato alle collisoni) mi tocchera definire a mano tutti gli stadi di rotazione
    if (falling_block.shape.size() != 4 || falling_block.shape[0].size() != 4){
        return; // per le forme insolite, non so se serve
    }

    // "ombra" temporanea per cambiare la forma 
    vector<vector<int>> newShape(4, vector<int>(4,0));
    for (int i=0; i<4; i++){
        for (int j=0; j<4; j++){
            newShape[i][j] = falling_block.shape[j][3-i];
        }
    }
    falling_block.shape = newShape;
    falling_block.rotation = (falling_block.rotation + 1) % 4;
}

bool isColliding(const Tetromino& block, const vector<vector<int>>& grid){
    //serve passare i parametri come const?
    for (int i=0; i<4; i++){          //tutti i tetramini hanno dimensione fissa, cancellato il check inutile di shape.size
        for (int j=0; j<4; i++){
            if (block.shape[i][j]==1 &&
                (block.y + i < 0 ||
                 block.y + i >= height ||
                 block.x + j < 0 ||
                 block.x + j >= width ||
                 grid[block.y + i][block.x + j] == 1)){
                    return true;
                }
        }
    }
    return false;
}

