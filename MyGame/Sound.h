#pragma once
#include <SDL_mixer.h>

extern Mix_Chunk *Move;
extern Mix_Chunk *Click;
extern Mix_Chunk *Hold;
extern Mix_Chunk *Down;
extern Mix_Chunk *Pause;
extern Mix_Chunk *Up;
extern Mix_Chunk *SoftDrop;
extern Mix_Chunk *DeleteLineSou;


extern Mix_Music *Music;

void loadSound();
void CloseSound();
