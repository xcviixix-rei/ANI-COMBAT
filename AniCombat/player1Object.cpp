#include "player1Object.h"

using namespace std;

player1Object :: player1Object()
{
    objectCond = true;

    frameTime = SDL_GetTicks();

    objectRect.x = objectRect.y = 0;

    objectPos.w = objectWidth = 75;
    objectPos.h = objectHeight = 35;
}

void player1Object :: initObjectPosition(int drt, SDL_Rect characterPos)
{
    charPos = characterPos;
    direction = drt;
    if(direction == 2) objectPos.x = charPos.x + charPos.w / 2;
    else if(direction == 1) objectPos.x = charPos.x - charPos.w / 2;
    objectPos.y = charPos.y + charPos.h / 3;
    objectCond = false;
}

void player1Object :: loadObjectIMG(SDL_Renderer* renderer)
{
    objectTexture = loadTexture("character/Naruto/narutoSpriteSheet/shurikenLeft.png", renderer);
    objectIMG.push_back(objectTexture); // objectIMG[0]
    objectTexture = loadTexture("character/Naruto/narutoSpriteSheet/shurikenRight.png", renderer);
    objectIMG.push_back(objectTexture); // objectIMG[1]
    SDL_QueryTexture(objectIMG[0], NULL, NULL, &sheetW, &sheetH);
    //0
}

void player1Object :: loadObject()
{
    if(direction == 1){
        flyingVelo = -12;
        objectTexture = objectIMG[0];
        objectRect.w = sheetW / 3;
        objectRect.h = sheetH;
    }
    else if(direction == 2){
        flyingVelo = 12;
        objectTexture = objectIMG[1];
        objectRect.w = sheetW / 3;
        objectRect.h = sheetH;
    }
}

void player1Object :: renderObject(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, objectTexture, &objectRect, &objectPos);
    objectPos.x += flyingVelo;
    if(SDL_GetTicks() - frameTime >= 30){
        objectRect.x += objectRect.w;
        frameTime = SDL_GetTicks();
    }
    if(objectRect.x >= sheetW){
        objectRect.x = 0;
    }
    if((objectPos.x + objectPos.w <= 0) || (objectPos.x >= screenW)){
        objectCond = true;
        objectTexture = nullptr;
    }
}
