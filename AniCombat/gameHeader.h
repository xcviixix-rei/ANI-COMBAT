#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

using namespace std;

void logSDLError(ostream& os, const string &msg, bool fatal);

void initSDL(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string WINDOW_TITLE, SDL_Window* &window, SDL_Renderer* &renderer, int &refreshRate);

void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

Mix_Chunk* loadSound (string path);

Mix_Music* loadSong (string path);

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer);

