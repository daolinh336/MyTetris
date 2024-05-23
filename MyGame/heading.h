#include <iostream>
#include <SDL.h>

using namespace std;



struct wrapTexture;

void logErrorAndExit(const char* msg, const char* error);

void logSDLError(std::ostream& os, const std::string &msg, bool fatal);///check error

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer, int SCREEN_WIDTH, int SCREEN_HEIGHT, const string& WINDOW_TITLE);///create cammera

void quitSDL(SDL_Window* window, SDL_Renderer* renderer); ///clear data

void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer);

SDL_Texture *loadTexture(const char *filename, SDL_Renderer* renderer);

void waitUntilKeyPressed();/// wait for press

void close();///clear data ver struct


