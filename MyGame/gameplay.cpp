#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include <SDL_ttf.h>

#include "gameplay.h"
#include "texture.h"



int PrePiece = -1;

extern int holded;
extern int period;
extern bool Blind;
extern bool gp;

int dem[7];
int t = 2;

int GetPrePosX [7][4] =
{
    {13, 13, 13, 13},
    {13, 14, 14, 14},
    {13, 14, 14, 14},
    {14, 14, 13, 14},
    {13, 14, 14, 14},
    {13, 14, 14, 14},
    {13, 14, 14, 14},
};

int GetPrePosY [7][4] =
{
    {9, 9, 9, 9},
    {10, 10, 10, 11},
    {10, 10, 10, 10},
    {10, 10, 10, 10},
    {10, 10, 10, 10},
    {10, 10, 10, 10},
    {10, 10, 10, 10},
};




int GetHoldPosX [7][4] =
{
    {13, 13, 13, 13},
    {13, 14, 14, 14},
    {13, 14, 14, 14},
    {14, 14, 13, 14},
    {13, 14, 14, 14},
    {13, 14, 14, 14},
    {13, 14, 14, 14},
};

int GetHoldPosY [7][4] =
{
    {2, 2, 2, 2},
    {2, 2, 2, 3},
    {3, 3, 3, 3},
    {3, 3, 3, 3},
    {3, 3, 3, 3},
    {3, 3, 3, 3},
    {3, 3, 3, 3},
};

void resetbag()
{
    t = 0;
    for(int i = 0; i <= 6; i++)dem[i] = 0;
}

Game::Game(Grid *pGrid, Tetromino *_gTetro, butve *pIO)
{
    mGrid = pGrid;
    gTetro = _gTetro;
    Ve = pIO;

    InitGame ();
}
int Game::GetRand (int a, int b)
{
    return rand () % (b - a + 1) + a;
}

void Game::InitGame()
{
    resetbag();
    mPiece			= GetRand(0,6);
    mRotation		= GetRand (0, 3);
    mPosX 			= 50 + gTetro-> Start(mPiece, mRotation, 0);
    mPosY 			= gTetro-> Start(mPiece, mRotation, 1);
    mColor = GetRand (1,6);
    dem[mPiece] = 1;
    t++;

    mNextPiece = GetRand(0,6);
    while(dem[mNextPiece] == 1)mNextPiece = (mNextPiece + 1)%6;

    mNextRotation 	= GetRand(0,3);
    mNextPosX 		= GetPrePosX[mNextPiece][mNextRotation];
    mNextPosY 	    = GetPrePosY[mNextPiece][mNextRotation];
    mNextColor = GetRand (1,6);

    dem[mNextPiece] = 1;
    t++;
}

void Game::exchange()
{
    if(holded == 0)
    {
        if(t==7)resetbag();
        mHoldPiece 		= GetRand (0, 6);
        while(dem[mHoldPiece] == 1)mHoldPiece = (mHoldPiece + 1 ) % 7;

        mHoldRotation 	= GetRand (0, 3);
        mHoldPosX 		= GetHoldPosX[mHoldPiece][mHoldRotation];
        mHoldPosY 	    = GetHoldPosY[mHoldPiece][mHoldRotation];

        mHoldColor = GetRand (1,6);
        mPosX = 5 + gTetro->Start (mPiece, mRotation, 0);
        mPosY = gTetro->Start(mPiece, mRotation, 1);

        t++;

        holded = 1;
    }
    int tg1 = mPiece;
    int tg2 = mRotation;
    int tg3 = mColor;
    mPiece			= mHoldPiece;
    mRotation		= mHoldRotation;
    mColor          = mHoldColor;

    mHoldPiece         = tg1;
    mHoldRotation      = tg2;
    mHoldColor         = tg3;
    mHoldPosX          = GetHoldPosX[mHoldPiece][mHoldRotation];
    mHoldPosY          = GetHoldPosY[mHoldPiece][mHoldRotation];
}

void Game::CreateNewPiece()
{
    if(t==7)resetbag();
    t++;

    mPiece			= mNextPiece;
    mRotation		= mNextRotation;
    mColor  		= mNextColor;
    mPosX 			= 5 + gTetro->Start(mPiece, mRotation, 0);
    mPosY 			= gTetro->Start(mPiece, mRotation, 1);

    mNextPiece = GetRand(0, 6);

    while(dem[mNextPiece] == 1)mNextPiece = (mNextPiece + 1) % 7;

    mNextRotation 	= GetRand(0, 3);
    mNextPosX 		= GetPrePosX[mNextPiece][mNextRotation];
    mNextPosY 	    = GetPrePosY[mNextPiece][mNextRotation];
    mNextColor = GetRand (1,6);

    dem[mNextPiece] = 1;
}

void Game::DrawPiece (int x, int y, int type, int rota)
{
    int RealX = 350 + x*30;
    int RealY = y*30;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (gTetro-> Type(type, rota, j, i) != 0)
            {
                Ve->DrawRectangle(RealX + i * square + 1, RealY + j * square + 1, square - 1, square - 1, mColor);
            }
        }
    }
}
void Game::DrawHoldPiece (int x, int y, int type, int rota)
{
    int RealX = 350 + x *square;
    int RealY = y*square;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (gTetro-> Type(type, rota, j, i) != 0)
            {
                Ve->DrawRectangle(RealX + i * square + 1, RealY + j * square + 1, square - 1, square - 1, mHoldColor);
                Ve->DrawKhungRectangle(RealX + i * square + 1, RealY + j * square + 1, square - 1, square - 1);
            }
        }
    }
}
void Game::DrawNextPiece (int x, int y, int type, int rota)
{
    int RealX = 350 + x *square;
    int RealY = y*square;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (gTetro-> Type(type, rota, j, i) != 0)
            {
                Ve->DrawRectangle(RealX + i * square + 1, RealY + j * square + 1, square - 1, square - 1, mNextColor);
                Ve->DrawKhungRectangle(RealX + i * square + 1, RealY + j * square + 1, square - 1, square - 1);
            }
        }
    }
}

void Game::DrawGhostPiece(int x, int y, int type, int rota)
{
    while (mGrid->CheckVar(x, y, type, rota))y++;
    y--;

    int RealX = 350 + x *square;
    int RealY = y*square;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (gTetro-> Type(type, rota, j, i) != 0)
            {
                Ve->DrawKhungRectangle(RealX + i * square + 1, RealY + j * square + 1, square - 1, square - 1);
            }
        }
    }
}

void Game::DrawGrid ()
{
    int x,y;
    SDL_GetMouseState(&x, &y);

    if(x >= 50 && x <= 104 && y >= 18 && y <= 68)SDL_RenderCopy(Ve->gRenderer, Ve->res1, NULL, NULL);
    else if(x >= 130 && x <= 188 && y >= 18 && y <= 88)SDL_RenderCopy(Ve->gRenderer, Ve->res2, NULL, NULL);
    else SDL_RenderCopy(Ve->gRenderer, Ve->res, NULL, NULL);

    int mX1 = 350 - 1;
    int mY = 0;

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (!mGrid->IsClear(i, j)  && !Blind)
                Ve->DrawRectangle (mX1 + i * square + 1,
                                   mY + j * square + 1,
                                   square - 1,
                                   square - 1,
                                   mGrid->GetColor(i,j));
        }
    }
}
void Game::DrawGrid_Time()
{
    int x,y;
    SDL_GetMouseState(&x, &y);

    SDL_RenderCopy(Ve->gRenderer, Ve->resTime, NULL, NULL);

    int mX1 = 350 - 1;
    int mY = 0;

    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        for (int j = 0; j < BOARD_HEIGHT; j++)
        {
            if (!mGrid->IsClear(i, j))
                Ve->DrawRectangle (mX1 + i * square + 1,
                                   mY + j * square + 1,
                                   square - 1,
                                   square - 1,
                                   mGrid->GetColor(i,j));
        }
    }
}
void Game::DrawScene ()
{
    DrawGrid ();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    if(gp)DrawGhostPiece (mPosX, mPosY, mPiece, mRotation);
    DrawNextPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
    if(holded)DrawHoldPiece (mHoldPosX, mHoldPosY, mHoldPiece, mHoldRotation);
}
void Game::DrawScene_Time()
{
    DrawGrid_Time();
    DrawPiece(mPosX, mPosY, mPiece, mRotation);
    if(gp)DrawGhostPiece (mPosX, mPosY, mPiece, mRotation);
    DrawNextPiece(mNextPosX, mNextPosY, mNextPiece, mNextRotation);
    if(holded)DrawHoldPiece (mHoldPosX, mHoldPosY, mHoldPiece, mHoldRotation);
}

