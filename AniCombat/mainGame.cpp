#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "gameHeader.h"
#include "background.h"
#include "character.h"

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

const string WINDOW_TITLE = "ANI - COMBAT";

int main(int argc, char* argv[]){
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, window, renderer);

    BG background;
    background.loadBG(renderer);

    CRT character;
    character.initPosition(background);

    SDL_Event e;

    bool gameRunning = true;

    while(gameRunning){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                gameRunning = false;
            }
            character.handleEvent(e);
        }
        character.move(SCREEN_WIDTH, SCREEN_HEIGHT);

        SDL_RenderClear(renderer);
        background.render(renderer);
        character.render(renderer);
        SDL_RenderPresent(renderer);

    }
    quitSDL(window, renderer);
    return 0;
}
