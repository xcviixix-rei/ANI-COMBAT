#include "flyingObjects.h"

using namespace std;
/*
flyingObjects :: flyingObjects()
{
    frameTime = SDL_GetTicks();

}

void flyingObjects :: loadObjectIMG(SDL_Renderer* renderer)
{

}

void CRT :: loadObject()
{
    object = nullptr;

    if(objectType == "shuriken"){
        objectVelo = 12;
        if(direction == 1){
            object = objectIMG[0];
            objectRect.w = objectSheetW[0] / 3;
            objectRect.h = objectSheetH[0];
        }
        else if(direction == 2){
            object = objectIMG[1];
            objectRect.w = objectSheetW[0] / 3;
            objectRect.h = objectSheetH[0];
        }
    }
}

void CRT :: renderObjects(SDL_Renderer* renderer){
    loadObject();
    if(objectType == "shuriken"){
        if(objectCond){
            objectPos.x = charPos.x;
            objectPos.y = charPos.y + charPos.h / 3;
            objectCond = false;
            if(direction == 1) shurikenVelo -= objectVelo;
            else if(direction == 2) shurikenVelo += objectVelo;
        }
        SDL_RenderCopy(renderer, object, &objectRect, &objectPos);
        if(SDL_GetTicks() - objectFrameTime >= 50){
            objectRect.x += objectRect.w;
            objectFrameTime = SDL_GetTicks();
        }
        if(objectRect.x >= objectSheetW[0]){
            objectRect.x = 0;
        }
        if(SDL_GetTicks() - objectMoveTime >= 10){
            objectPos.x += shurikenVelo;
            objectMoveTime = SDL_GetTicks();
        }
        if( ( objectPos.x + charPos.w < 0 ) || ( objectPos.x > background.screenW) ){
            object = nullptr;
            objectType.clear();
            shurikenVelo = 0;
            objectVelo = 0;
            objectMoveTime = SDL_GetTicks();
        }
    }
}

*/
