#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "character.h"
#include "background.h"
#include "gameHeader.h"

#define cend(a) cout << a << endl
#define twocend(a,b) cout << a << " : " << b << endl

using namespace std;

CRT :: CRT()
{
    frameTime = SDL_GetTicks();
    objectFrameTime = SDL_GetTicks();
    startTime = SDL_GetTicks();

    charRect.x = charRect.y = 0;
    objectRect.x = objectRect.y = 0;
    objectPos.w = 100;
    objectPos.h = 50;

    charStat = "stand";
    direction = 2;

    skillCond = false;
    objectCond = false;

    w = h =0;

    veloX = 0;
    veloY = 0;

    jumpTime = SDL_GetTicks();
    normalAtkTime = SDL_GetTicks();
    throwShurikenTime = SDL_GetTicks();

    charPos.w = char_width;
    charPos.h = char_height;
    charPos.x = 50;
}

void CRT :: initPosition(BG background){
    charPos.y = background.groundPos.y - charPos.h + 16;
}

void CRT :: loadIMG(SDL_Renderer* renderer){
    charIMG[0] = loadTexture("character/Naruto/narutoSpriteSheet/standLeft.png", renderer);
    charIMG[1] = loadTexture("character/Naruto/narutoSpriteSheet/standRight.png", renderer);
    SDL_QueryTexture(charIMG[0], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //0

    charIMG[2] = loadTexture("character/Naruto/narutoSpriteSheet/runLeft.png", renderer);
    charIMG[3] = loadTexture("character/Naruto/narutoSpriteSheet/runRight.png", renderer);
    SDL_QueryTexture(charIMG[2], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //1

    charIMG[4] = loadTexture("character/Naruto/narutoSpriteSheet/jumpUpLeft.png", renderer);
    charIMG[5] = loadTexture("character/Naruto/narutoSpriteSheet/jumpUpRight.png", renderer);
    SDL_QueryTexture(charIMG[4], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //2

    charIMG[6] = loadTexture("character/Naruto/narutoSpriteSheet/fallDownLeft.png", renderer);
    charIMG[7] = loadTexture("character/Naruto/narutoSpriteSheet/fallDownRight.png", renderer);
    SDL_QueryTexture(charIMG[6], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //3

    charIMG[8] = loadTexture("character/Naruto/narutoSpriteSheet/normalAtkLeft.png", renderer);
    charIMG[9] = loadTexture("character/Naruto/narutoSpriteSheet/normalAtkRight.png", renderer);
    SDL_QueryTexture(charIMG[8], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //4

    charIMG[10] = loadTexture("character/Naruto/narutoSpriteSheet/throwShurikenLeft.png", renderer);
    charIMG[11] = loadTexture("character/Naruto/narutoSpriteSheet/throwShurikenRight.png", renderer);
    SDL_QueryTexture(charIMG[10], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //5


    objectIMG[0] = loadTexture("character/Naruto/narutoSpriteSheet/shurikenLeft.png", renderer);
    objectIMG[1] = loadTexture("character/Naruto/narutoSpriteSheet/shurikenRight.png", renderer);
    SDL_QueryTexture(objectIMG[0], NULL, NULL, &w, &h);
    objectSheetW.push_back(w); objectSheetH.push_back(h);
    //0
}

void CRT :: handleEvent(SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                veloX -= char_velo;
                direction = 1;
                if(charPos.y == jumpCurrentHeight){
                    charStat = "run";
                    charRect.x = 0;
                }
                break;

            case SDLK_d:
                veloX += char_velo;
                direction = 2;
                if(charPos.y == jumpCurrentHeight){
                    charStat = "run";
                    charRect.x = 0;
                }
                break;

            case SDLK_w:
                if(charPos.y == jumpCurrentHeight){
                    charStat = "jumpUp";
                    charRect.x = 0;
                    veloY = - 1.5 * char_velo;
                    jumpTime = SDL_GetTicks();
                }
                break;

            case SDLK_j:
                if((SDL_GetTicks() - normalAtkTime >= 120) && (charPos.y == jumpCurrentHeight)){
                    charRect.x = 0;
                    charStat = "normalAtk";
                    skillCond = true;
                }
                break;

            case SDLK_u:
                if((SDL_GetTicks() - throwShurikenTime >= 1000) && (charPos.y == jumpCurrentHeight)){
                    charRect.x = 0;
                    charStat = "throwShuriken";
                    objectType = "shuriken";
                    skillCond = true;
                    objectCond = true;
                    objectMoveTime = SDL_GetTicks();
                }
                break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                veloX += char_velo;
                if(charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    charStat = "stand";
                }
                break;

            case SDLK_d:
                veloX -= char_velo;
                if(charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    charStat = "stand";
                }
                break;

            case SDLK_j:
                if(charPos.y == jumpCurrentHeight && charStat == "normalAtk"){
                    charRect.x = 0;
                    skillCond = false;
                }
                break;

            case SDLK_u:
                if(charPos.y == jumpCurrentHeight && charStat == "throwShuriken"){
                    charRect.x = 0;
                    skillCond = false;
                }
                break;
        }
    }
}

void CRT :: move( SDL_Renderer* renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, BG &background)
{
    if(SDL_GetTicks() - startTime >= 5){

        startTime = SDL_GetTicks();

        charPos.x += veloX;

        if( ( charPos.x < 0 ) || ( charPos.x + char_width > SCREEN_WIDTH ) )
        {
            charPos.x -= veloX;
        }

        charPos.y += veloY;

        if(charStat == "jumpUp" || charStat == "fallDown"){
            if(SDL_GetTicks() - jumpTime >= 60){
                veloY += 2;
                jumpTime = SDL_GetTicks();
            }
        }

        if(charPos.y < jumpCurrentHeight){
            if(veloY > 0)
            {
                charStat = "fallDown";
            }
            else if(veloY <= 0)
            {
                charStat = "jumpUp";
            }
        }

        if( charPos.y > background.groundPos.y - charPos.h + 16 )
        {
            charPos.y = background.groundPos.y - charPos.h + 16 ;
            veloY = 0;
            jumpTime = SDL_GetTicks();
        }

        checkJumpPlace(renderer, background);

        if(veloY > 0){
            previousVeloY = veloY;
        }
        if(previousVeloY > 0 && veloY == 0){
            previousVeloY = 0;
            jumpCurrentHeight = charPos.y;
            jumpTime = SDL_GetTicks();
            charRect.x = 0;
            charStat = "stand";
            frameTime = SDL_GetTicks();
        }
    }
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

void CRT :: loadChar()
{
    charMotion = nullptr;

    if(charStat == "stand"){
        if(direction == 1){
            charMotion = charIMG[0];
            charRect.w = sheetW[0] / 4;
            charRect.h = sheetH[0];
        }
        else if(direction == 2){
            charMotion = charIMG[1];
            charRect.w = sheetW[0] / 4;
            charRect.h = sheetH[0];
        }
    }
    if(charStat == "run"){
        if(veloX < 0){
            charMotion = charIMG[2];
            charRect.w = sheetW[1] / 8;
            charRect.h = sheetH[1];
            direction = 1;
        }
        else if(veloX > 0){
            charMotion = charIMG[3];
            charRect.w = sheetW[1] / 8;
            charRect.h = sheetH[1];
            direction = 2;
        }
    }
    if(charStat == "jumpUp"){
        if(direction == 1){
            charMotion = charIMG[4];
            charRect.w = sheetW[2] / 2;
            charRect.h = sheetH[2];
        }
        else if(direction == 2){
            charMotion = charIMG[5];
            charRect.w = sheetW[2] / 2;
            charRect.h = sheetH[2];
        }
    }
    if(charStat == "fallDown"){
        if(direction == 1){
            charMotion = charIMG[6];
            charRect.w = sheetW[3] / 2;
            charRect.h = sheetH[3];
        }
        else if(direction == 2){
            charMotion = charIMG[7];
            charRect.w = sheetW[3] / 2;
            charRect.h = sheetH[3];
        }
    }
    if(charStat == "normalAtk"){
        if(direction == 1){
            charMotion = charIMG[8];
            charRect.w = sheetW[4] / 4;
            charRect.h = sheetH[4];
        }
        else if(direction == 2){
            charMotion = charIMG[9];
            charRect.w = sheetW[4] / 4;
            charRect.h = sheetH[4];
        }
    }
    if(charStat == "throwShuriken"){
        if(direction == 1){
            charMotion = charIMG[10];
            charRect.w = sheetW[5] / 6;
            charRect.h = sheetH[5];
        }
        else if(direction == 2){
            charMotion = charIMG[11];
            charRect.w = sheetW[5] / 6;
            charRect.h = sheetH[5];
        }
    }
}

void CRT :: renderObjects(SDL_Renderer* renderer, BG background){
    loadObject();

    if(objectType == "shuriken"){
        if(objectCond){
            objectPos.x = charPos.x ;
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

void CRT :: renderSkill(SDL_Renderer* renderer, BG &background){
    if(charStat == "normalAtk" ){
        charPos.w = 90;
        charPos.h = 93;
        if(direction == 1){
            charPos.x -= 8;
        }
        while(skillCond){
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            renderObjects(renderer, background);
            SDL_RenderPresent(renderer);
            if(SDL_GetTicks() - frameTime >= 50){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x > sheetW[4] - charRect.w){
                charRect.x = 0;
                skillCond = false;
            }
        }
        if(direction == 1){
            charPos.x += 8;
        }
        charStat = "stand";
        charPos.w = char_width;
        charPos.h = char_height;
        normalAtkTime = SDL_GetTicks();
    }
    if(charStat == "throwShuriken" ){
        while(skillCond){
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            renderObjects(renderer, background);
            SDL_RenderPresent(renderer);
            if(SDL_GetTicks() - frameTime >= 50){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x > sheetW[5] - charRect.w){
                charRect.x = 0;
                skillCond = false;
            }
        }
        charStat = "stand";
        charPos.w = char_width;
        charPos.h = char_height;
        throwShurikenTime = SDL_GetTicks();
    }
}

void CRT :: render(SDL_Renderer* renderer, BG &background)
{
    loadChar();

    if(charStat == "stand"){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        renderObjects(renderer, background);
        SDL_RenderPresent(renderer);
        if(SDL_GetTicks() - frameTime >= 100){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[0]){
            charRect.x = 0;
        }
        jumpCurrentHeight = charPos.y;
    }
    else if(charStat == "run"){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        renderObjects(renderer, background);
        SDL_RenderPresent(renderer);
        if(SDL_GetTicks() - frameTime >= 80){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[1]){
            charRect.x = 0;
        }
        jumpCurrentHeight = charPos.y;
        if(veloX == 0) charStat = "stand";
    }
    else if(charStat == "jumpUp"){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        renderObjects(renderer, background);
        SDL_RenderPresent(renderer);
        if(SDL_GetTicks() - frameTime >= 80){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[2]){
            charRect.x = 0;
        }
    }
    else if(charStat == "fallDown"){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        renderObjects(renderer, background);
        SDL_RenderPresent(renderer);
        if(SDL_GetTicks() - frameTime >= 80){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[3]){
            charRect.x = 0;
        }
    }
    else{
        frameTime = SDL_GetTicks();
        renderSkill(renderer, background);
    }
    if(veloY == 0 && charPos.y == jumpCurrentHeight && veloX != 0) charStat = "run";
}

void CRT :: checkJumpPlace(SDL_Renderer* renderer, BG& background)
{
    if( (charPos.y + char_height >= background.jumpPlacePos[4].y + 8) && (charPos.y + char_height <= background.jumpPlacePos[4].y + 20) && (charPos.x >= background.jumpPlacePos[4].x - 50) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[4].y - char_height + 14;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[3].y + 8) && (charPos.y + char_height <= background.jumpPlacePos[3].y + 20) && (charPos.x <= background.jumpPlacePos[3].w - 30) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[3].y - char_height + 14;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[2].y + 8) && (charPos.y + char_height <= background.jumpPlacePos[2].y + 20) && (charPos.x >= background.jumpPlacePos[2].x - 50) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[2].y - char_height + 14;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[1].y + 8) && (charPos.y + char_height <= background.jumpPlacePos[1].y + 20) && (charPos.x <= background.jumpPlacePos[1].w - 30) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[1].y - char_height + 14;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[0].y ) && (charPos.y + char_height <= background.jumpPlacePos[0].y + 28) && (charPos.x >= background.jumpPlacePos[0].x - 50) && (charPos.x <= background.jumpPlacePos[0].x + background.jumpPlacePos[0].w - 30)){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[0].y - char_height + 14;
        }
    }
    else if( ( (charPos.y + char_height == background.jumpPlacePos[4].y + 14) && (charPos.x < background.jumpPlacePos[4].x - 50) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[3].y + 14) && (charPos.x > background.jumpPlacePos[3].w - 30) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[2].y + 14) && (charPos.x < background.jumpPlacePos[2].x - 50) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[1].y + 14) && (charPos.x > background.jumpPlacePos[1].w - 30) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[0].y + 14) && ((charPos.x < background.jumpPlacePos[0].x - 50) || (charPos.x > background.jumpPlacePos[0].x + background.jumpPlacePos[0].w - 30)))){
        if(veloY == 0){
            veloY = 2;
            charStat = "fallDown";
            jumpTime = SDL_GetTicks();
            jumpCurrentHeight = background.groundPos.y - charPos.h + 16;
        }
    }
}

/*
bool checkCollision( SDL_Rect a, SDL_Rect b)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    return true;
}
*/
