#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "tetromino.h"

using namespace std;

int Tetromino::Type(int id, int rota, int pX, int pY)
{
    return Block[id][rota][pX][pY];
}

int Tetromino::Start(int id, int rota, int d)
{
    return StartId[id][rota][d];
}



