#include "statusBar1.h"

using namespace std;

statusBar1 :: statusBar1(int healthPoint, SDL_Renderer* renderer)
{
    currentHP = maxHP = healthPoint;

    healthBar = loadTexture("character/Naruto/narutoSpriteSheet/statusHPBar.png", renderer);
    statusBar = loadTexture("character/Naruto/narutoSpriteSheet/statusBar.png", renderer);
    lostHPBar = loadTexture("character/Naruto/narutoSpriteSheet/lostHPBar.png", renderer);
    blankHPBar = loadTexture("character/Naruto/narutoSpriteSheet/blankHPBar.png", renderer);

    lostHPBarPos.w = healthBarPos.w = maxHPBarWidth;
    statusBarPos.w = 192;
    lostHPBarPos.h = healthBarPos.h = statusBarPos.h = 70;

    statusBarPos.x = 10;
    lostHPBarPos.x = healthBarPos.x = 42;
    lostHPBarPos.y = healthBarPos.y = statusBarPos.y = 10;

    blankHPBarPos = healthBarPos;
    blankHPBarPos.x += 3;

    updateHPLostTime = SDL_GetTicks();
}

void statusBar1 :: updateHP(int healthPoint)
{
    currentHP = healthPoint;
    healthBarPos.w = maxHPBarWidth * currentHP / maxHP;
    if(SDL_GetTicks() - updateHPLostTime >= 1500){
        if(lostHPBarPos.w > healthBarPos.w){
            lostHPBarPos.w -= 1;
        }
        else{
            lostHPBarPos.w = healthBarPos.w;
            updateHPLostTime = SDL_GetTicks();
        }
    }
}


void statusBar1 :: renderStatus(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, blankHPBar, NULL, &blankHPBarPos);
    SDL_RenderCopy(renderer, lostHPBar, NULL, &lostHPBarPos);
    SDL_RenderCopy(renderer, healthBar, NULL, &healthBarPos);
    SDL_RenderCopy(renderer, statusBar, NULL, &statusBarPos);
}
