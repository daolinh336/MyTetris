#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "gamepause.h"
#include "draw.h"
#include "Sound.h"

extern int period;
extern int quit, WaitCount, StopTimeTotal, pausetime;
extern bool ft;
extern butve Ve;

extern bool sf;

int pausepos(int x, int y)
{
    if(x >= 199 && x <= 420 && 353 <= y && y <= 442)return 1;
    else if(x >= 579 && x <= 800 && 353 <= y && y <= 442)return 2;
    else return 0;
}

void loadpausebg(int k)
{
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    if(k == 1)imageSurface = IMG_Load("img/PauseScreen_resume.png");
    else if (k == 2)imageSurface = IMG_Load("img/PauseScreen_MainMenu.png");
    else imageSurface = IMG_Load("img/PauseScreen.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);
}
void pausegame()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
    int k = pausepos(x,y);
    loadpausebg(k);
    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int k = pausepos(x,y);
            if( k == 1)period = 21;
            else if ( k == 2)
            {
                Reset();
                period = 1;
            }
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}
void pausegame_Time()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int k = pausepos(x,y);
            if( k == 1)
            {
                StopTimeTotal += SDL_GetTicks() - pausetime;
                period = 22;
            }
            else if (k == 2)
            {
                WaitCount = 0;
                ft = 0;
                StopTimeTotal = 0;
                pausetime = 0;
                Reset();
                period = 1;
            }
        }
        else
        {
            int k = pausepos(x,y);
            loadpausebg(k);
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}


