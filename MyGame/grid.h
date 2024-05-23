#pragma once
#include "tetromino.h"
#include "Number.h"

#define square 30
#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

class Grid
{
public:

    Grid						(Number *num, Tetromino *_gTetro);

    int GetColor            	(int i, int j);
    bool IsClear			(int x, int y);
    bool CheckVar		(int x, int y, int type, int rota);
    void Store			(int x, int y, int type, int rota, int color);
    void Scan();
    bool IsGameOver();
    void InitGrid();

    int mGrid[BOARD_WIDTH][BOARD_HEIGHT];
    Tetromino *gTetro;
    Number *mNum;
    int mScreenHeight;

    void DeleteLine (int y);
};
