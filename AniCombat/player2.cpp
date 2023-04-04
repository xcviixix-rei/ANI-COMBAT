#include "player2.h"

using namespace std;

player2 :: player2(BG bg)
{
    frameTime = SDL_GetTicks();
    startTime = SDL_GetTicks();

    charRect.x = charRect.y = 0;

    previousCharStat = charStat = stand;

    skillCond = false;
    normalAttackCond = false;
    throwingObjectCond = false;

    w = h = 0;

    veloX = 0;
    veloY = 0;

    jumpTime = SDL_GetTicks();
    normalAttackTime = SDL_GetTicks();
    throwingObjectTime = SDL_GetTicks();

    background = bg;

    healthPoints = 1000;

    char_width = 150;
    char_height = 96;
}

void player2 :: initplayer2()
{
    direction = 1;
    charPos.w = char_width;
    charPos.h = char_height;
    charPos.x = background.screenW - char_width - 50;
    charPos.y = background.groundPos.y - charPos.h + 16;
}

void player2 :: loadIMG(SDL_Renderer* renderer)
{
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/standLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[0]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/standRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[1]
    SDL_QueryTexture(charIMG[0], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //0

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/runLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[2]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/runRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[3]
    SDL_QueryTexture(charIMG[2], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //1

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/jumpUpLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[4]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/jumpUpRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[5]
    SDL_QueryTexture(charIMG[4], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //2

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/fallDownLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[6]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/fallDownRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[7]
    SDL_QueryTexture(charIMG[6], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //3

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/normalAttackLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[8]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/normalAttackRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[9]
    SDL_QueryTexture(charIMG[8], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //4

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/getsugaTenshouLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[10]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/getsugaTenshouRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[11]
    SDL_QueryTexture(charIMG[10], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //5
}
void player2 :: handleEvent(SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                if(!skillCond){
                    veloX -= char_velo;
                    direction = 1;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = run;
                    }
                }
                break;

            case SDLK_RIGHT:
                if(!skillCond){
                    veloX += char_velo;
                    direction = 2;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = run;
                    }
                }
                break;

            case SDLK_UP:
                if(charPos.y == jumpCurrentHeight && !skillCond){
                    charStat = jumpUp;
                    veloY = - 1.5 * char_velo;
                    jumpTime = SDL_GetTicks();
                }
                break;

            case SDLK_1:
                if((SDL_GetTicks() - normalAttackTime >= 120) && (charPos.y == jumpCurrentHeight)){
                    tmpVelo = veloX;
                    charStat = normalAttack;
                    frameTime = SDL_GetTicks();
                    skillCond = true;
                    normalAttackCond = true;
                }
                break;

            case SDLK_4:
                if((SDL_GetTicks() - throwingObjectTime >= 1000) && (charPos.y == jumpCurrentHeight)){
                    tmpVelo = veloX;
                    charStat = getsugaTenshou;
                    skillCond = true;
                    throwingObjectCond = true;
                }
                break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_LEFT:
                if(!skillCond){
                    veloX += char_velo;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = stand;
                    }
                }
                break;

            case SDLK_RIGHT:
                if(!skillCond){
                    veloX -= char_velo;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = stand;
                    }
                }
                break;
        }
    }
}

void player2 :: loadChar()
{
    charMotion = nullptr;

    charPos.w = char_width;
    charPos.h = char_height;

    if(charStat == stand){
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
    if(charStat == run){
            charPos.w = 160;
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
    if(charStat == jumpUp){
            charPos.w = 120;
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
    if(charStat == fallDown){
            charPos.w = 120;
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
    if(charStat == normalAttack){
        if(direction == 1){
            charMotion = charIMG[8];
            charRect.w = sheetW[4] / 6;
            charRect.h = sheetH[4];
        }
        else if(direction == 2){
            charMotion = charIMG[9];
            charRect.w = sheetW[4] / 6;
            charRect.h = sheetH[4];
        }
    }
    if(charStat == getsugaTenshou){
        if(direction == 1){
            charMotion = charIMG[10];
            charRect.w = sheetW[5] / 8;
            charRect.h = sheetH[5];
        }
        else if(direction == 2){
            charMotion = charIMG[11];
            charRect.w = sheetW[5] / 8;
            charRect.h = sheetH[5];
        }
    }
}

void player2 :: renderSkill(SDL_Renderer* renderer)
{

}
