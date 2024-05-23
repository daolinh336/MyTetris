#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "draw.h"
#include "texture.h"
#include "Sound.h"
#include "highscore.h"


extern butve Ve;
extern int period ;
extern bool quit, sf, gp, mp ;

void settings()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);

    ///-----------
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    if(gp)imageSurface = IMG_Load("img/SettingsYes.png");
    else imageSurface = IMG_Load("img/SettingsNo.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);
    ///------------------
    LTexture ad(&Ve);
    if(mp)
    {
        ad.loadHScore("ON");
        ad.render(400, 452);
    }
    else
    {
        ad.loadHScore("OFF");
        ad.render(385, 452);
    }
    LTexture ad1(&Ve);

    if(sf)
    {
        ad1.loadHScore("ON");
        ad1.render(620, 452);
    }
    else
    {
        ad1.loadHScore("OFF");
        ad1.render(615, 452);
    }

    ad.free();
    ad1.free();
    ///------------------------------

    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            if(47 <= x && x <= 98 && 22 <= y && y<= 72)period = 1;
            else if(683 <= x && x <= 735 && 185 <= y && y<= 230)
            {
                if(gp == 1)gp = 0;
                else gp = 1;
            }
            else if(357 <= x && x <= 613 && 262 <= y && y<= 337)period = 8;
            else if(375 <= x && x <= 605 && 361 <= y && y<= 424)period = 9;
            else if(255 <= x && x <= 456 && 451 <= y && y<= 510)
            {
                if(mp == 0)mp = 1;
                else mp = 0;
            }
            else if(551 <= x && x <= 754 && 448 <= y && y<= 510)
            {
                if(sf == 0)sf = 1;
                else sf = 0;
            }
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}
void HowToPlay()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
///------------------------
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    imageSurface = IMG_Load("img/HowToPlay.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);
    ///---------------

    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            if(47 <= x && x <= 98 && 22 <= y && y<= 72)period = 7;
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}


void UpdateHighScore(int newScore)
{
    adu.push_back(newScore);
    sort(adu.begin(),adu.end());

    int l = adu.size();
    dc.clear();

    dc.push_back(getxau(adu[l - 1]));
    dc.push_back(getxau(adu[l - 2]));
    dc.push_back(getxau(adu[l - 3]));
    dc.push_back(getxau(adu[l - 4]));
    dc.push_back(getxau(adu[l - 5]));

}

void HighScore()
{
    SDL_Event e;
    int x,y;
    SDL_GetMouseState(&x, &y);
///---------------
    SDL_Surface* imageSurface = NULL;
    SDL_Texture* res = NULL;

    imageSurface = IMG_Load("img/DiemCao.png");

    res = SDL_CreateTextureFromSurface(Ve.gRenderer, imageSurface);

    SDL_RenderCopy(Ve.gRenderer, res, NULL, NULL);

    SDL_DestroyTexture(res);
    SDL_FreeSurface(imageSurface);

///---------------

    LTexture ad(&Ve);

    ad.loadHScore(dc[0]);
    ad.render(500, 185);
    ad.loadHScore(dc[1]);
    ad.render(500, 225);
    ad.loadHScore(dc[2]);
    ad.render(500, 270);
    ad.loadHScore(dc[3]);
    ad.render(500, 315);
    ad.loadHScore(dc[4]);
    ad.render(500, 360);

    ad.free();
///-----------------------

    while( SDL_PollEvent( &e ) != 0)
    {
        if( e.type == SDL_QUIT )quit = true;
        else if(e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            if(sf)Mix_PlayChannel( -1, Click, 0 );
            if(47 <= x && x <= 98 && 22 <= y && y<= 72)period = 7;
            else if (311 <= x && 754 >= x && 432 <= y && y <= 510)
            {
                dc[0] = dc[1] = dc[2] = dc[3] = dc[4] = "0";
                adu.clear();
                int k = 5;
                while(k--)adu.push_back(0);
            }
        }
    }
    SDL_RenderPresent( Ve.gRenderer );
}
void ResetHighScore()
{
    dc[0] = "0";
    dc[1] = "0";
    dc[2] = "0";
    dc[3] = "0";
    dc[4] = "0";
}
