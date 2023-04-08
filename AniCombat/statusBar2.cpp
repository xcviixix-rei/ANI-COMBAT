#include "statusBar2.h"

using namespace std;

statusBar2 :: statusBar2(int healthPoint, SDL_Renderer* renderer)
{
    currentHP = maxHP = healthPoint;

    healthBar = loadTexture("character/Ichigo/ichigoSpriteSheet/statusHPBar.png", renderer);
    statusBar = loadTexture("character/Ichigo/ichigoSpriteSheet/statusBar.png", renderer);
    lostHPBar = loadTexture("character/Ichigo/ichigoSpriteSheet/lostHPBar.png", renderer);

    lostHPBarPos.w = healthBarPos.w = maxHPBarWidth;
    statusBarPos.w = 176;
    lostHPBarPos.h = healthBarPos.h = statusBarPos.h = 70;

    statusBarPos.x = screenW - statusBarPos.w - 10;
    lostHPBarPos.x = healthBarPos.x = statusBarPos.x + 10;
    lostHPBarPos.y = healthBarPos.y = statusBarPos.y = 10;

    updateHPLostTime = SDL_GetTicks();
}

void statusBar2 :: updateHP(int healthPoint)
{
    currentHP = healthPoint;
    healthBarPos.w = maxHPBarWidth * currentHP / maxHP;
    healthBarPos.x = screenW - healthBarPos.w - 10 - 34;
    if(SDL_GetTicks() - updateHPLostTime >= 800){
        lostHPBarPos.w = healthBarPos.w;
        lostHPBarPos.x = healthBarPos.x;
        updateHPLostTime = SDL_GetTicks();
    }
}


void statusBar2 :: renderStatus(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, lostHPBar, NULL, &lostHPBarPos);
    SDL_RenderCopy(renderer, healthBar, NULL, &healthBarPos);
    SDL_RenderCopy(renderer, statusBar, NULL, &statusBarPos);
}

