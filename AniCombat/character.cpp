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
    startTime = SDL_GetTicks();

    charRect.x = charRect.y = 0;

    charStat = "stand";
    direction = 2;

    skillCond = false;

    w = h =0;

    veloX = 0;
    veloY = 0;

    jumpTime = SDL_GetTicks();
    normalAtkTime = SDL_GetTicks();

    charPos.w = char_width;
    charPos.h = char_height;
    charPos.x = 50;
}

void CRT :: initPosition(BG background){
    charPos.y = background.groundPos.y - charPos.h + 16;
}

void CRT :: loadIMG(SDL_Renderer* renderer){
    charIMG[0] = loadTexture("character/Naruto/standLeft.png", renderer);
    charIMG[1] = loadTexture("character/Naruto/standRight.png", renderer);
    SDL_QueryTexture(charIMG[0], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //0

    charIMG[2] = loadTexture("character/Naruto/runLeft.png", renderer);
    charIMG[3] = loadTexture("character/Naruto/runRight.png", renderer);
    SDL_QueryTexture(charIMG[2], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //1

    charIMG[4] = loadTexture("character/Naruto/jumpUpLeft.png", renderer);
    charIMG[5] = loadTexture("character/Naruto/jumpUpRight.png", renderer);
    SDL_QueryTexture(charIMG[4], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //2

    charIMG[6] = loadTexture("character/Naruto/fallDownLeft.png", renderer);
    charIMG[7] = loadTexture("character/Naruto/fallDownRight.png", renderer);
    SDL_QueryTexture(charIMG[6], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //3

    charIMG[8] = loadTexture("character/Naruto/normalAtkLeft.png", renderer);
    charIMG[9] = loadTexture("character/Naruto/normalAtkRight.png", renderer);
    SDL_QueryTexture(charIMG[8], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //4

}

void CRT :: handleEvent(SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                if(charPos.y == jumpCurrentHeight){
                    charStat = "run";
                    charRect.x = 0;
                }
                veloX -= char_velo;
                direction = 1;
                break;

            case SDLK_d:
                if(charPos.y == jumpCurrentHeight){
                    charStat = "run";
                    charRect.x = 0;
                }
                veloX += char_velo;
                direction = 2;
                break;

            case SDLK_w:
                if(charPos.y == jumpCurrentHeight){
                    charStat = "jumpUp";
                    charRect.x = 0;
                    veloY = - 1.5 * char_velo;
                    skillCond = true;
                    jumpTime = SDL_GetTicks();
                }
                break;

            case SDLK_j:
                if((SDL_GetTicks() - normalAtkTime >= 120) && charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    charStat = "normalAtk";
                    skillCond = true;
                }
                break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                if(charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    charStat = "stand";
                }
                veloX += char_velo;
                break;

            case SDLK_d:
                if(charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    charStat = "stand";
                }
                veloX -= char_velo;
                break;

            case SDLK_j:
                if(charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    skillCond = false;
                    charStat = "stand";
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
            skillCond = false;
            jumpCurrentHeight = charPos.y;
            jumpTime = SDL_GetTicks();
            charRect.x = 0;
            charStat = "stand";
            frameTime = SDL_GetTicks();
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
    if(veloY == 0 && charPos.y == jumpCurrentHeight){
        if(veloX < 0){
            charStat = "run";
            charMotion = charIMG[2];
            charRect.w = sheetW[1] / 8;
            charRect.h = sheetH[1];
            direction = 1;
        }
        else if(veloX > 0){
            charStat = "run";
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
            SDL_RenderPresent(renderer);
            if(SDL_GetTicks() - frameTime >= 70){
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
}

void CRT :: render(SDL_Renderer* renderer, BG &background)
{
    loadChar();

    cend(charStat);
    if(charMotion == nullptr) cend("NOOOOOOOOO");

    if(charStat == "stand"){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
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
            skillCond = true;
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
