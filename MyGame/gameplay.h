#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<bits/stdc++.h>
#include "grid.h"
#include "draw.h"
#include <time.h>

#define WAIT_TIME 100

class Game
{
public:

    Game		(Grid *pBoard, Tetromino *types, butve *pIO);

    void DrawScene ();
    void DrawScene_Time ();
    void CreateNewPiece ();
    void exchange();
    void InitGame();

    int mPosX, mPosY;
    int mPiece, mRotation;
    int mColor;
    int mHoldPiece, mHoldRotation;

    int mNextPosX, mNextPosY;
    int mNextPiece, mNextRotation;
    int mNextColor;

    int mHoldPosX, mHoldPosY;
    int mHoldColor;

    Grid *mGrid;
    Tetromino *gTetro;
    butve *Ve;

    int GetRand (int a, int b);

    void DrawPiece (int x, int y, int type, int rota);
    void DrawGhostPiece (int x, int y, int type, int rota);
    void DrawNextPiece (int x, int y, int type, int rota);
    void DrawHoldPiece (int x, int y, int type, int rota);

    void RenderGamePlay(int x, int y);

    void DrawGrid ();
    void DrawGrid_Time();

};
