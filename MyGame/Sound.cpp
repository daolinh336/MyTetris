#include <SDL_mixer.h>

Mix_Chunk *Move = NULL;
Mix_Chunk *Click = NULL;
Mix_Chunk *Hold = NULL;
Mix_Chunk *Down = NULL;
Mix_Chunk *Pause = NULL;
Mix_Chunk *Up = NULL;
Mix_Chunk *SoftDrop = NULL;
Mix_Chunk *DeleteLineSou = NULL;

Mix_Music *Music = NULL;

#include<iostream>

#include "Sound.h"

using namespace std;
void loadSound()
{

    //Load music
    Music = Mix_LoadMUS( "Music/Music.wav" );

    Move = Mix_LoadWAV( "Music/Move.wav" );

    Click = Mix_LoadWAV( "Music/Click.wav" );
    Hold = Mix_LoadWAV( "Music/Hold.wav" );
    Down = Mix_LoadWAV( "Music/Down.wav" );
    Up = Mix_LoadWAV( "Music/Up.wav" );
    SoftDrop = Mix_LoadWAV( "Music/softdrop.wav" );
    Pause = Mix_LoadWAV( "Music/Pause.wav" );
    Hold = Mix_LoadWAV( "Music/Pause.wav" );
    DeleteLineSou = Mix_LoadWAV( "Music/DeleteLine.wav" );



    Mix_PlayMusic( Music, -1 );
}

void CloseSound()
{
    Mix_FreeChunk( Move );
    Mix_FreeChunk( Click );
    Mix_FreeChunk( Hold );
    Mix_FreeChunk( Down );
    Mix_FreeChunk( Pause );
    Mix_FreeChunk( Up );
    Move = NULL;
    Click = NULL;
    Hold = NULL;
    Down = NULL;
    Pause = NULL;
    Up = NULL;

    Mix_Quit();
}
