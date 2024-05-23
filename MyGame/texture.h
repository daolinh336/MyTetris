#pragma once
#include "draw.h"

class LTexture
{
public:
    LTexture(butve *pIO);

    ~LTexture();

    void free();

    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

    void loadFromRenderedText(std::string textureText);
    void loadHScore(std::string textureText);

    int getWidth();
    int getHeight();

    SDL_Texture* mTexture;

    butve *mIO;

    int mWidth;
    int mHeight;
};
