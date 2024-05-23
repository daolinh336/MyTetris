#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "gameover.h"
#include "texture.h"
#include "Sound.h"

extern butve Ve;
extern int period ;
extern bool quit, sf, ft ;
extern int WaitCount, StopTimeTotal, pausetime;


string renderScore, renderLine, renderLevel;

int GameOverPos(int x, int y)
{
    if(x >= 199 && x <= 420 && 383 <= y && y <= 472)return 1;
    else if(x >= 579 && x <= 800 && 383 <= y && y <= 472)return 2;
    else return 0;
}
void LoadGameOver(int k)
{
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    if (k == 1)imageSurface = IMG_Load("img/GameOver_PlayAgain.png");
    else if (k == 2)imageSurface = IMG_Load("img/GameOver_MainMenu.png");
    else imageSurface = IMG_Load("img/GameOver.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);

    LTexture ad(&Ve);
    ad.loadHScore(renderLevel);
    ad.render(500, 209);
    ad.loadHScore(renderLine);
    ad.render(500, 265);
    ad.loadHScore(renderScore);
    ad.render(500, 325);
    ad.free();
}

void GameOver()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
    int k = GameOverPos(x,y);
    LoadGameOver(k);

    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int k = GameOverPos(x,y);
            if( k == 1)
            {
                WaitCount = 0;
                ft = 0;
                StopTimeTotal = 0;
                pausetime = 0;
                period = 21;
            }
            else if(k == 2)
            {
                WaitCount = 0;
                ft = 0;
                StopTimeTotal = 0;
                pausetime = 0;
                period = 1;
            }
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}
void GameOver_Time()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
    int k = GameOverPos(x,y);
    LoadGameOver(k);

    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int k = GameOverPos(x,y);
            if( k == 1)
            {
                WaitCount = 0;
                ft = 0;
                StopTimeTotal = 0;
                pausetime = 0;
                period = 22;
            }
            else if(k == 2)
            {
                WaitCount = 0;
                ft = 0;
                StopTimeTotal = 0;
                pausetime = 0;
                period = 1;
            }
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}

