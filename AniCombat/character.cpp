#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "character.h"
#include "background.h"
#include "gameHeader.h"

using namespace std;

CRT :: CRT()
{
    startTime = 0;

    frameTime = 0;
    frameNum = 0;

    charRect.x = charRect.y = 0;

    direction = 2;

    skillCond = false;

    collider.w = char_width;
    collider.h = char_height;

    w = h =0;

    veloX = 0;
    veloY = 0;

    charPos.w = 70;
    charPos.h = 84;
    charPos.x = 50;
}

void CRT :: initPosition(BG background){
    charPos.y = background.groundPos.y - charPos.h + 14;
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

    charIMG[4] = loadTexture("character/Naruto/jumpLeft.png", renderer);
    charIMG[5] = loadTexture("character/Naruto/jumpRight.png", renderer);
    SDL_QueryTexture(charIMG[4], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //2

    charIMG[6] = loadTexture("character/Naruto/normalAtkLeft.png", renderer);
    charIMG[7] = loadTexture("character/Naruto/normalAtkRight.png", renderer);
    SDL_QueryTexture(charIMG[6], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //3

}

void CRT :: handleEvent(SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                charRect.x = 0;
                veloX -= char_velo;
                direction = 1;
                break;

            case SDLK_d:
                charRect.x = 0;
                veloX += char_velo;
                direction = 2;
                break;

            case SDLK_w:
                charStat = "jump";
                charRect.x = 0;
                veloY = - 1.25 * char_velo;
                break;

            case SDLK_j:
                charRect.x = 0;
                charStat = "normalAtk";
                skillCond = true;
                break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                veloX += char_velo;
                charRect.x = 0;
                break;

            case SDLK_d:
                veloX -= char_velo;
                charRect.x = 0;
                break;

            case SDLK_w:
                charStat.clear();
                veloY = 1.25 * char_velo;
                charRect.x = 0;
                break;

            case SDLK_j:
                charStat.clear();
                charRect.x = 0;
                skillCond = false;
                break;
        }
    }
}

void CRT :: move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT)
{
    charPos.x += veloX;
	collider.x = charPos.x;

    if( ( charPos.x < 0 ) || ( charPos.x + char_width > SCREEN_WIDTH ) )
    {
        charPos.x -= veloX;
		collider.x = charPos.x;
    }

    charPos.y += veloY;
    jumpCurrentHeight += veloY;
	collider.y = charPos.y;

    if(  charPos.y < 0 || ( charPos.y + char_height > SCREEN_HEIGHT - 20) || abs(jumpCurrentHeight) > jumpHeightMax )
    {
        charPos.y -= veloY;
		collider.y = charPos.y;
		charRect.x = 0;
		veloY = 0;
        if(charPos.y < 0 || abs(jumpCurrentHeight) > jumpHeightMax){
           veloY = 1.25 * char_velo;
        }
    }

}

void CRT :: loadChar()
{
    charMotion = NULL;

    if(charStat.empty()){
        if( veloX == 0 && veloY == 0){
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
        else if(veloX != 0 && veloY == 0){
            if(veloX < 0){
                charMotion = charIMG[2];
                charRect.w = sheetW[1] / 8;
                charRect.h = sheetH[1];
            }
            else if(veloX > 0){
                charMotion = charIMG[3];
                charRect.w = sheetW[1] / 8;
                charRect.h = sheetH[1];
            }
        }
        else if(veloY != 0){
            if(direction == 1){
                charMotion = charIMG[4];
                charRect.w = sheetW[2] / 8;
                charRect.h = sheetH[2];
            }
            else if(direction == 2){
                charMotion = charIMG[5];
                charRect.w = sheetW[2] / 8;
                charRect.h = sheetH[2];
            }
        }
    }
    else if(!charStat.empty()){
        if(charStat == "normalAtk"){
            if(direction == 1){
                charMotion = charIMG[6];
                charRect.w = sheetW[3] / 4;
                charRect.h = sheetH[3];
            }
            else if(direction == 2){
                charMotion = charIMG[7];
                charRect.w = sheetW[3] / 4;
                charRect.h = sheetH[3];
            }
        }
    }
}

void CRT :: renderSkill(SDL_Renderer* renderer, BG &background){
    if(charStat == "normalAtk" ){
        while(skillCond){
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            SDL_RenderPresent(renderer);
            if(frameTime == 10){
                charRect.x += charRect.w;
                if(charRect.x > sheetW[3] - charRect.w){
                    charRect.x = 0;
                    skillCond = false;
                }
                frameTime = 0;
            }
            frameTime ++;
        }
        charStat.clear();
    }
    else if(charStat == "jump" ){
        while(skillCond){
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            SDL_RenderPresent(renderer);
            if(frameTime == 10){
                charRect.x += charRect.w;
                if(charRect.x > sheetW[2] - charRect.w){
                    charRect.x = 0;
                    skillCond = false;
                }
                frameTime = 0;
            }
            frameTime ++;
        }
        charStat.clear();
    }
}

void CRT :: render(SDL_Renderer* renderer, BG &background)
{
    loadChar();

    if(charStat.empty()){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        SDL_RenderPresent(renderer);
        if(veloX == 0) w = sheetW[0];
        else if(veloX != 0) w = sheetW[1];
        if(frameTime == 10){
            charRect.x += charRect.w;
            if(charRect.x > w - charRect.w){
                charRect.x = 0;
            }
            frameTime = 0;
        }
        SDL_Delay(10);
        frameTime ++;
    }
    else if(!charStat.empty()){
        renderSkill(renderer, background);
    }
}

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

