#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>

#include "draw.h"
#include "ChooseMode.h"
#include "Sound.h"

extern butve Ve;
extern bool Blind, quit;

extern int period, sf;

void loadchoosemode()
{
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    imageSurface = IMG_Load("img/ChooseMode.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);
}

void ChooseMode()
{
    Blind = 0;
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
    loadchoosemode();
    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            if(47 <= x && x <= 98 && 22 <= y && y<= 72)period = 1;
            else if (372 <= x && 663 >= x && 262 <= y && y <= 312)period = 21;
            else if (367 <= x && 661 >= x && 355 <= y && y <= 415)period = 22;
            else if (367 <= x && 661 >= x && 444 <= y && y <= 503)
            {
                Blind = 1;
                period = 21;
            }
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}
