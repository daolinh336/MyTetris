#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<bits/stdc++.h>


#include "grid.h"
#include "Sound.h"

extern bool sf;

Grid::Grid (Number *num, Tetromino *_gTetro)
{
    gTetro = _gTetro;

    mNum = num;

    InitGrid();
}

void Grid::InitGrid()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
        for (int j = 0; j < BOARD_HEIGHT; j++)
            mGrid[i][j] = 0;
}

void Grid::Store(int x, int y, int pPiece, int pRotation, int pColor)
{
    for (int i1 = x, i2 = 0; i1 < x + 5; i1++, i2++)
    {
        for (int j1 = y, j2 = 0; j1 < y + 5; j1++, j2++)
        {
            if (gTetro->Type(pPiece, pRotation, j2, i2) != 0)
                mGrid[i1][j1] = pColor;
        }
    }
}

int Grid :: GetColor(int i,int j)
{
    return mGrid[i][j];
}

bool Grid::IsGameOver()
{
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (mGrid[i][0] != 0)return true;
    }
    return false;
}

void Grid::DeleteLine (int y)
{
    if(sf)Mix_PlayChannel( -1, DeleteLineSou, 0 );
    for (int j = y; j > 0; j--)
    {
        for (int i = 0; i < BOARD_WIDTH; i++)
        {
            mGrid[i][j] = mGrid[i][j-1];
        }
    }
}

void Grid::Scan()
{
    for (int j = 0; j < BOARD_HEIGHT; j++)
    {
        int i = 0;
        while (i < BOARD_WIDTH)
        {
            if (mGrid[i][j] == 0) break;
            i++;
        }
        if (i == BOARD_WIDTH)
        {
            mNum -> PlusLine();
            mNum -> PlusScore(50);
            DeleteLine(j);
        }
    }
}

bool Grid::IsClear (int x, int y)
{
    if (mGrid [x][y] == 0) return true;
    else return false;
}

bool Grid::CheckVar(int x, int y, int type, int rota)
{
    for (int i1 = x, i2 = 0; i1 < x + 5; i1++, i2++)
    {
        for (int j1 = y, j2 = 0; j1 < y + 5; j1++, j2++)
        {
            if ( i1 < 0 || i1 >= BOARD_WIDTH || j1 >= BOARD_HEIGHT)
            {
                if (gTetro->Type(type, rota, j2, i2) != 0)return false;
            }
            if (j1 >= 0)
            {
                if ((gTetro->Type (type, rota, j2, i2) != 0) &&
                        (!IsClear (i1, j1))	)return false;
            }
        }
    }
    return true;
}
