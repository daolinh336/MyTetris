#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "gameplay.h"
#include "texture.h"
#include "GamePause.h"
#include "Sound.h"
#include "highscore.h"
#include "gameover.h"
#include "Settings.h"
#include "Menu.h"
#include "ChooseMode.h"

using namespace std;

bool mp = 1;
bool sf = 1;
bool ft = 0;


int tg1, tg2;

bool Blind = 0;
int kct = 60000;
int Count;

int WaitCount, StopTimeTotal, pausetime;

bool quit = false;

TTF_Font *fixedsys;


int period = 1;

bool gp = 1;

int holded = 0;
Tetromino tetromino;

butve Ve;

LTexture td();
Number num(&Ve);

Grid gGrid (&num, &tetromino);

Game gGame (&gGrid, &tetromino, &Ve);

int k = SDL_GetTicks();

void Reset()
{
    holded = 0;
    gGrid.InitGrid();
    gGame.InitGame();
    num.PlusScore((-1)*num.Score);
    num.ResetLine();
}

string makeClock(int k)
{
    int mmm, s;
    if(k==120)
    {
        return "02:00";
    }
    else if(k>=60)
    {
        k-=60;
        mmm = 1;
    }
    else mmm = 0;
    string ans = "0";
    ans += char(mmm + '0');
    ans += ":";
    ans += char(k/10 + '0');
    ans += char(k%10 + '0');

    return ans;
}

void DrawTime()
{
    int remainTime =   60 - ( SDL_GetTicks() - StopTimeTotal - WaitCount) / 1000;
    if(remainTime<=0)
    {
        renderLevel = num.getLevel();
        renderScore = num.getScore();
        renderLine = num.getLine();
        ft = 0;
        Reset();
        period = 62;
        return;
    }


    string now = makeClock(remainTime);

    LTexture ad(&Ve);
    ad.loadFromRenderedText(now);

    ad.render(770, 515);
    ad.free();
}

void TimePlay()
{
    Ve.ClearScreen();
    gGame.DrawScene_Time();
    num.DrawNumber();
    num.UpdateLevel(num.Score);
    DrawTime();
    Ve.UpdateScreen();

    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.key.repeat == 0)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x >= 50 && x <= 104 && y >= 18 && y <= 68)
            {
                Reset();
                WaitCount = 0;
                ft = 0;
                StopTimeTotal = 0;
                pausetime = 0;
                period = 1;
                return;
            }
            else if(x >= 130 && x <= 188 && y >= 18 && y <= 88)
            {
                pausetime = SDL_GetTicks();
                period = 52;
                return;
            }
        }
        else if (e.type == SDL_KEYDOWN)
        {
            int press = e.key.keysym.sym;
            if(press == SDLK_LEFT && gGrid.CheckVar (gGame.mPosX - 1, gGame.mPosY, gGame.mPiece, gGame.mRotation))
            {
                if(sf)Mix_PlayChannel( -1, Move, 0 );
                gGame.mPosX--;
            }
            else if(press == SDLK_RIGHT && gGrid.CheckVar (gGame.mPosX + 1, gGame.mPosY, gGame.mPiece, gGame.mRotation))
            {
                if(sf)Mix_PlayChannel( -1, Move, 0 );
                gGame.mPosX++;
            }
            else if(press == SDLK_DOWN && gGrid.CheckVar (gGame.mPosX, gGame.mPosY + 1, gGame.mPiece, gGame.mRotation))
            {
                if(sf)Mix_PlayChannel( -1, SoftDrop, 0 );
                gGame.mPosY++;
            }
            else if(press == SDLK_SPACE)
            {
                if(sf)Mix_PlayChannel( -1, Down, 0 );
                int st = gGame.mPosY;
                while (gGrid.CheckVar(gGame.mPosX, st, gGame.mPiece, gGame.mRotation))st++;

                while(gGrid.CheckVar(gGame.mPosX, gGame.mPosY, gGame.mPiece, gGame.mRotation))gGame.mPosY++;

                gGrid.Store(gGame.mPosX, gGame.mPosY - 1, gGame.mPiece, gGame.mRotation, gGame.mColor);

                gGrid.Scan();

                if(gGrid.IsGameOver())gGrid.InitGrid();

                gGame.CreateNewPiece();
                Ve.ClearScreen();
            }
            else if(press == SDLK_UP)
            {
                if(sf)Mix_PlayChannel( -1, Up, 0 );
                if (gGrid.CheckVar (gGame.mPosX, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                else if(gGrid.CheckVar (gGame.mPosX - 1, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX--;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                else if(gGrid.CheckVar (gGame.mPosX + 1, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX++;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                ///danh rieng cho khoi nam ngang
                else if(gGrid.CheckVar (gGame.mPosX - 2, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX-=2;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                else if(gGrid.CheckVar (gGame.mPosX + 2, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX+=2;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                ///------------------------------
            }
            else if(press == SDLK_c && gGrid.CheckVar (gGame.mPosX, gGame.mPosY, gGame.mHoldPiece, gGame.mHoldRotation))
            {
                if(sf)Mix_PlayChannel( -1, SoftDrop, 0 );
                gGame.exchange();
            }
            else if(press == SDLK_m)
            {
                if(sf == 0)sf = 1;
                else if(sf == 1)sf = 0;
                if(mp == 0)mp = 1;
                else if(mp == 1)mp = 0;
            }
        }
    }
    tg2 = SDL_GetTicks();

    if ((tg2 - tg1) > 800)
    {
        if (gGrid.CheckVar(gGame.mPosX, gGame.mPosY + 1, gGame.mPiece, gGame.mRotation))gGame.mPosY++;
        else
        {
            gGrid.Store(gGame.mPosX, gGame.mPosY, gGame.mPiece, gGame.mRotation, gGame.mColor);
            gGrid.Scan();
            if(gGrid.IsGameOver())gGrid.InitGrid();
            gGame.CreateNewPiece();
        }
        tg1 = SDL_GetTicks();
    }
}

void gameplay()
{
    Ve.ClearScreen();
    gGame.DrawScene();
    num.DrawNumber();
    Ve.UpdateScreen();
    num.UpdateLevel(num.Score);

    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0)
    {
        if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT && e.key.repeat == 0)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int x, y;
            SDL_GetMouseState(&x, &y);
            if(x >= 50 && x <= 104 && y >= 18 && y <= 68)
            {
                Reset();
                period = 1;
                return;
            }
            else if(x >= 130 && x <= 188 && y >= 18 && y <= 88)
            {
                period = 51;
                return;
            }
        }
        else if (e.type == SDL_KEYDOWN)
        {
            int press = e.key.keysym.sym;
            if(press == SDLK_LEFT && gGrid.CheckVar (gGame.mPosX - 1, gGame.mPosY, gGame.mPiece, gGame.mRotation))
            {
                if(sf)Mix_PlayChannel( -1, Move, 0 );
                gGame.mPosX--;
            }
            else if(press == SDLK_RIGHT && gGrid.CheckVar (gGame.mPosX + 1, gGame.mPosY, gGame.mPiece, gGame.mRotation))
            {
                if(sf)Mix_PlayChannel( -1, Move, 0 );
                gGame.mPosX++;
            }
            else if(press == SDLK_DOWN && gGrid.CheckVar (gGame.mPosX, gGame.mPosY + 1, gGame.mPiece, gGame.mRotation))
            {
                if(sf)Mix_PlayChannel( -1, SoftDrop, 0 );
                gGame.mPosY++;
                num.PlusScore(1);
            }
            else if(press == SDLK_SPACE)
            {
                if(sf)Mix_PlayChannel( -1, Down, 0 );
                int st = gGame.mPosY;
                while (gGrid.CheckVar(gGame.mPosX, st, gGame.mPiece, gGame.mRotation))st++;
                num.PlusScore((st - gGame.mPosY) * 2);

                while(gGrid.CheckVar(gGame.mPosX, gGame.mPosY, gGame.mPiece, gGame.mRotation))gGame.mPosY++;

                gGrid.Store(gGame.mPosX, gGame.mPosY - 1, gGame.mPiece, gGame.mRotation, gGame.mColor);

                gGrid.Scan();

                if (gGrid.IsGameOver())
                {
                    renderLevel = num.getLevel();
                    renderScore = num.getScore();
                    renderLine = num.getLine();
                    UpdateHighScore(num.Score);
                    Reset();
                    period = 61;
                }
                gGame.CreateNewPiece();
                Ve.ClearScreen();
            }
            else if(press == SDLK_UP)
            {
                if(sf)Mix_PlayChannel( -1, Up, 0 );
                if (gGrid.CheckVar (gGame.mPosX, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                else if(gGrid.CheckVar (gGame.mPosX - 1, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX--;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                else if(gGrid.CheckVar (gGame.mPosX + 1, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX++;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                ///danh rieng cho khoi nam ngang
                else if(gGrid.CheckVar (gGame.mPosX - 2, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX-=2;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                else if(gGrid.CheckVar (gGame.mPosX + 2, gGame.mPosY, gGame.mPiece, (gGame.mRotation + 1) % 4))
                {
                    gGame.mPosX+=2;
                    gGame.mRotation = (gGame.mRotation + 1) % 4;
                }
                ///------------------------------
            }
            else if(press == SDLK_c && gGrid.CheckVar (gGame.mPosX, gGame.mPosY, gGame.mHoldPiece, gGame.mHoldRotation))
            {
                if(sf)Mix_PlayChannel( -1, SoftDrop, 0 );
                gGame.exchange();
            }
            else if(press == SDLK_m)
            {
                if(sf == 0)sf = 1;
                else if(sf == 1)sf = 0;
                if(mp == 0)mp = 1;
                else if(mp == 1)mp = 0;
            }
        }
    }
    tg2 = SDL_GetTicks();
    if ((tg2 - tg1) > 800 - (num.Level - 1)*40)
    {
        if (gGrid.CheckVar(gGame.mPosX, gGame.mPosY + 1, gGame.mPiece, gGame.mRotation))gGame.mPosY++;
        else
        {
            gGrid.Store(gGame.mPosX, gGame.mPosY, gGame.mPiece, gGame.mRotation, gGame.mColor);
            gGrid.Scan();
            if (gGrid.IsGameOver())
            {
                renderLevel = num.getLevel();
                renderScore = num.getScore();
                renderLine = num.getLine();
                UpdateHighScore(num.Score);
                Reset();
                period = 61;
            }
            gGame.CreateNewPiece();
        }
        tg1 = SDL_GetTicks();
    }
}
int main( int argc, char* args[] )
{
    loadSound();
    fixedsys = TTF_OpenFont("fixedsys.ttf", 50);
    freopen("highscore.txt", "r", stdin);

    InHighScore();
    preHighScore();

    while (!quit)
    {
        if(mp == 1)Mix_ResumeMusic();
        else if(mp == 0)Mix_PauseMusic();
        if(period == 1)menu();
        else if(period == 7)settings();
        else if(period == 2)ChooseMode();
        else if(period == 22)
        {
            if(ft == 0)
            {
                WaitCount = SDL_GetTicks(), ft = 1;
            }
            TimePlay();
        }
        else if(period == 21)gameplay();
        else if (period == 4)quit = true;
        else if(period == 51)pausegame();
        else if(period == 52)pausegame_Time();
        else if(period == 61)GameOver();
        else if(period == 62)GameOver_Time();
        else if(period == 8)HowToPlay();
        else if(period == 9)HighScore();
    }

    freopen("highscore.txt", "w", stdout);
    for(int i = 0; i <= 4; i++)cout << dc[i] << endl;
    return 0;
}


