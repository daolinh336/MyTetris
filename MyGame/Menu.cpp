#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>

#include "draw.h"
#include "Sound.h"

extern butve Ve;
extern int period ;
extern bool quit, sf, gp, mp ;


void loadbg(int k)
{
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    if(k==1)imageSurface = IMG_Load("img/background_normal.png");
    else if (k == 2)imageSurface = IMG_Load("img/background_start.png");
    else if (k == 3)imageSurface = IMG_Load("img/background_settings.png");
    else imageSurface = IMG_Load("img/background_exit.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);
}


int bgpos(int x, int y)
{
    if(420 <= x && x <= 588 && 342 <= y && y <= 393)return 2;
    else if(420 <= x && x <= 588 && 425 <= y && y <= 476)return 3;
    else if(420 <= x && x <= 588 && 512 <= y && y <= 563)return 4;
    else return 1;
}

void menu()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
    int k = bgpos(x,y);
    loadbg(k);
    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            int k = bgpos(x,y);
            if( k == 2)period = 2;/// vao game
            else if(k == 3)period = 7;///background
            else if (k == 4)period = 4;///exit
        }
        else
        {
            k = bgpos(x,y);
            loadbg(k);
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}
