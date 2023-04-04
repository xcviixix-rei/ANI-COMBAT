#include "gameHeader.h"
#include "background.h"
#include "player1.h"
#include "player2.h"

using namespace std;

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 720;

const string WINDOW_TITLE = "ANI - COMBAT";

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    initSDL(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE, window, renderer);

    BG background;
    background.loadBG(renderer);

    player1 plr1(background);
    plr1.initplayer1();
    plr1.loadIMG(renderer);

    player2 plr2(background);
    plr2.initplayer2();
    plr2.loadIMG(renderer);

    SDL_Event e;

    SDL_DisplayMode current;
    if (SDL_GetCurrentDisplayMode(0, &current) != 0)
    {
        SDL_Log("Could not get display mode for video display #%d: %s", 0, SDL_GetError());
    }
    int refreshRate = current.refresh_rate;

    bool gameRunning = true;

    while(gameRunning)
    {
        SDL_Delay(refreshRate / 9);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
            {
                gameRunning = false;
            }
            plr1.handleEvent(e);
            plr2.handleEvent(e);
        }
        plr1.move();
        plr2.move();

        SDL_RenderClear(renderer);
        background.render(renderer);
        plr1.render(renderer);
        plr2.render(renderer);
        SDL_RenderPresent(renderer);
    }
    quitSDL(window, renderer);
    return 0;
}


