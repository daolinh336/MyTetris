#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include<bits/stdc++.h>
using namespace std;

const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

class butve
{
public:

    butve();
    ~butve();
    void free();
    void renderbg();
    void renderbg_Time();
    void init();
    void DrawRectangle		(int pX1, int pY1, int pX2, int pY2, int pC);
    void DrawKhungRectangle		(int pX1, int pY1, int pX2, int pY2);
    void ClearScreen		();

    void UpdateScreen		();




    SDL_Renderer* gRenderer;
    SDL_Window* gWindow;
    SDL_Texture* res = NULL;
    SDL_Texture* res1 = NULL;
    SDL_Texture* res2 = NULL;
    SDL_Texture* resTime = NULL;

};


