#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <SDL_ttf.h>

#include "texture.h"

using namespace std;

extern TTF_Font *fixedsys;

LTexture::LTexture(butve *pIO)
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
    mIO = pIO;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}


void LTexture::loadFromRenderedText( std::string textureText)
{

    SDL_Color textColor = {0, 255, 0};

    SDL_Surface* textSurface = TTF_RenderText_Solid( fixedsys, textureText.c_str(), textColor );

    mTexture = SDL_CreateTextureFromSurface(mIO -> gRenderer, textSurface );

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
}

void LTexture::loadHScore( std::string textureText)
{
    SDL_Color textColor = {0, 0, 0};

    SDL_Surface* textSurface = TTF_RenderText_Solid( fixedsys, textureText.c_str(), textColor );

    mTexture = SDL_CreateTextureFromSurface(mIO -> gRenderer, textSurface );

    mWidth = textSurface->w;
    mHeight = textSurface->h;

    SDL_FreeSurface(textSurface);
}


void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx( mIO -> gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

