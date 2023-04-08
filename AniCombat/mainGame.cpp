#include "gameHeader.h"
#include "background.h"
#include "player1.h"
#include "player2.h"
#include "statusBar1.h"
#include "statusBar2.h"
#include "collision.h"

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

    statusBar1 stat1(plr1.healthPoints, renderer);

    player2 plr2(background);
    plr2.initplayer2();
    plr2.loadIMG(renderer);

    statusBar2 stat2(plr2.healthPoints, renderer);

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

        collisionBetweenPlayer(plr1, plr2);

        stat1.updateHP(plr1.healthPoints);
        stat2.updateHP(plr2.healthPoints);

        SDL_RenderClear(renderer);
        background.render(renderer);
        plr1.render(renderer);
        plr2.render(renderer);
        stat1.renderStatus(renderer);
        stat2.renderStatus(renderer);
        SDL_RenderPresent(renderer);
    }
    quitSDL(window, renderer);
    return 0;
}


