#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "draw.h"

using namespace std;

struct mau
{
    int r, g, b;
};
mau bangmau[9];
void taomau()
{
    bangmau[0].r = 0;
    bangmau[0].g = 0;
    bangmau[0].b = 0;

    bangmau[1].r = 255;
    bangmau[1].g = 0;
    bangmau[1].b = 0;

    bangmau[2].r = 255;
    bangmau[2].g = 165;
    bangmau[2].b = 0;

    bangmau[3].r = 255;
    bangmau[3].g = 192;
    bangmau[3].b = 203;

    bangmau[4].r = 0;
    bangmau[4].g = 255;
    bangmau[4].b = 255;

    bangmau[5].r = 255;
    bangmau[5].g = 255;
    bangmau[5].b = 255;

    bangmau[6].r = 173;
    bangmau[6].g = 216;
    bangmau[6].b = 230;
}
///-----------------

butve::butve()
{
    init();
    taomau();
    renderbg();
    renderbg_Time();
}

butve::~butve()
{
    free();
}
void butve ::free()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyTexture(res);
    SDL_DestroyTexture(res1);
    SDL_DestroyTexture(res2);
}
void butve::ClearScreen()
{
    SDL_SetRenderDrawColor(gRenderer, 225, 235, 190, 255);
    SDL_RenderClear(gRenderer);
}

void butve::DrawRectangle(int pX1, int pY1, int pX2, int pY2, int color)
{
    SDL_Rect Rect= {pX1, pY1, pX2, pY2};
    SDL_SetRenderDrawColor(gRenderer, bangmau[color].r, bangmau[color].g, bangmau[color].b, 255);
    SDL_RenderFillRect(gRenderer, &Rect);
}

void butve::DrawKhungRectangle(int pX1, int pY1, int pX2, int pY2)
{
    SDL_Rect Rect= {pX1, pY1, pX2, pY2};

    SDL_SetRenderDrawColor(gRenderer, bangmau[5].r, bangmau[5].g, bangmau[5].b, 255);
    SDL_RenderDrawRect(gRenderer, &Rect);
}
void butve::renderbg()
{
    SDL_Surface* imageSurface = NULL;

    imageSurface = IMG_Load("img/background_game.png");
    res = SDL_CreateTextureFromSurface(gRenderer, imageSurface);

    imageSurface = IMG_Load("img/background_game1.png");
    res1 = SDL_CreateTextureFromSurface(gRenderer, imageSurface);

    imageSurface = IMG_Load("img/background_game2.png");
    res2 = SDL_CreateTextureFromSurface(gRenderer, imageSurface);

    SDL_FreeSurface(imageSurface);
}
void butve::renderbg_Time()
{
    SDL_Surface* imageSurface = NULL;

    imageSurface = IMG_Load("img/background_gameTime.png");
    resTime = SDL_CreateTextureFromSurface(gRenderer, imageSurface);

    SDL_FreeSurface(imageSurface);
}
void butve::UpdateScreen()
{
    SDL_RenderPresent(gRenderer);
}
void butve::init()
{
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
    }
    else
    {
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        gWindow = SDL_CreateWindow( "Tetrisewy", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            }
            else
            {
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                }
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                }
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
                }
            }
        }
    }
    return ;
}
