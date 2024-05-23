#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>

#include "texture.h"
#include "draw.h"

#include<bits/stdc++.h>
using namespace std;


class Number
{
public:

    Number(butve *pIO);

    int Line = 0;
    int Score = 0;

    int Level = 1;

    butve *Ve;


    SDL_Texture* res;
    SDL_Texture* res1;
    SDL_Texture* res2;

    string getLine();
    string getScore();
    string getLevel();

    void UpdateLevel(int score);
    void PlusScore(int num);
    void PlusLine();
    void ResetLine();


    void DrawLineScore(int line);
    void DrawScore(int score);
    void DrawLevel(int level);

    void DrawNumber();
};



