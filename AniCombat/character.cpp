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
    startTime = 0;

    frameTime = 0;

    charRect.x = charRect.y = 0;

    charStat = "stand";
    direction = 2;

    skillCond = false;

    w = h =0;

    veloX = 0;
    veloY = 0;
    jumpTime = 0;

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
                charStat = "jump";
                if(charPos.y == jumpCurrentHeight){
                    charRect.x = 0;
                    veloY = - char_velo;
                    skillCond = true;
                    jumpTime = 0;
                }
                break;

            case SDLK_j:
                if((SDL_GetTicks() - startTime >= 120) && charPos.y == jumpCurrentHeight){
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
                    charStat = "stand";
                    charRect.x = 0;
                    skillCond = false;
                }
                break;
        }
    }
}

void CRT :: move(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, BG &background)
{
    charPos.x += veloX;

    if( ( charPos.x < 0 ) || ( charPos.x + char_width > SCREEN_WIDTH ) )
    {
        charPos.x -= veloX;
    }
    charPos.y += veloY;

    if(jumpTime == 20){
        veloY += 2;
        jumpTime = 0;
    }
    jumpTime ++;

    if( charPos.y > background.groundPos.y - charPos.h + 16 )
    {
        charPos.y -= veloY;
        veloY = 0;
        jumpTime = 0;
    }
}

void CRT :: loadChar()
{
    charMotion = NULL;

    if((charStat == "stand" || veloX == 0) && !skillCond){
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
    if(veloY == 0){
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
    if(charStat == "jump" && skillCond){
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
    if(charStat == "normalAtk" && skillCond){
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

void CRT :: renderSkill(SDL_Renderer* renderer, BG &background){
    if(charStat == "normalAtk" ){
        charPos.w = 87;
        while(skillCond){
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            SDL_RenderPresent(renderer);
            if(frameTime == 10){
                charRect.x += charRect.w;
                frameTime = 0;
            }
            if(charRect.x > sheetW[3] - charRect.w){
                charRect.x = 0;
                skillCond = false;
            }
            frameTime ++;
        }
        charStat = "stand";
        charPos.w = char_width;
        charPos.h = char_height;
        frameTime = 0;
        startTime = SDL_GetTicks();
    }
}

void CRT :: render(SDL_Renderer* renderer, BG &background)
{
    loadChar();

    if(charStat == "stand" && !skillCond){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        SDL_RenderPresent(renderer);
        if(frameTime == 13){
            charRect.x += charRect.w;
            frameTime = 0;
        }
        if(charRect.x >= sheetW[0]){
            charRect.x = 0;
        }
        frameTime ++;
        jumpCurrentHeight = charPos.y;
    }
    else if(charStat == "run" && !skillCond){
        SDL_RenderClear(renderer);
        background.render(renderer);
        SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
        SDL_RenderPresent(renderer);
        if(frameTime == 13){
            charRect.x += charRect.w;
            frameTime = 0;
        }
        if(charRect.x >= sheetW[1]){
            charRect.x = 0;
        }
        frameTime ++;
        jumpCurrentHeight = charPos.y;
        if(veloX == 0) charStat = "stand";
    }
    else if(charStat == "jump" && skillCond || veloY != 0){
        if( (charPos.y == jumpCurrentHeight - char_velo) && veloY < 0){
            charRect.x = 0;
            for(int i = 0; i < 10; i++){
                SDL_RenderClear(renderer);
                background.render(renderer);
                SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
                SDL_RenderPresent(renderer);
            }
            charRect.x = charRect.w;
            frameTime = 0;
        }
        else if((charPos.y < jumpCurrentHeight - char_velo) && veloY < 0){
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            SDL_RenderPresent(renderer);
            if(frameTime == 10){
                charRect.x += charRect.w;
                frameTime = 0;
            }
            if(charRect.x > 2 * charRect.w){
                charRect.x = charRect.w;
            }
            frameTime++;
        }
        else if((charPos.y < jumpCurrentHeight - char_velo) && veloY == 0){
            if(direction == 1) charPos.x += 12;
            else if(direction == 2) charPos.x -= 12;
            charRect.x = 3 * charRect.w;
            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            SDL_RenderPresent(renderer);
            frameTime = 0;
            if(direction == 1) charPos.x -= 12;
            else if(direction == 2) charPos.x += 12;
        }
        else if((charPos.y < jumpCurrentHeight - char_velo) && veloY > 0){
            if(direction == 1) charPos.x += 12;
            else if(direction == 2) charPos.x -= 12;

            SDL_RenderClear(renderer);
            background.render(renderer);
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            SDL_RenderPresent(renderer);
            if(frameTime == 10){
                charRect.x += charRect.w;
                frameTime = 0;
            }
            if(charRect.x > 4 * charRect.w){
                charRect.x = 3 * charRect.w;
            }
            frameTime++;
            if(direction == 1) charPos.x -= 12;
            else if(direction == 2) charPos.x += 12;
        }
        else if( (charPos.y == jumpCurrentHeight - char_velo) && veloY > 0){
            charRect.x = 5 * charRect.w;
            frameTime = 0;
            bool jumpCond = true;
            while(jumpCond){
                charPos.y = jumpCurrentHeight + 10;
                SDL_RenderClear(renderer);
                background.render(renderer);
                SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
                SDL_RenderPresent(renderer);
                if(frameTime == 5){
                    charRect.x += charRect.w;
                    frameTime = 0;
                }
                if(charRect.x > 7 * charRect.w){
                    charRect.x = 0;
                    jumpCond = false;
                    skillCond = false;
                    frameTime = 0;
                    charPos.y = jumpCurrentHeight;
                }
                frameTime++;
            }
            charRect.x = 0;
            frameTime = 0;
            charStat = "stand";
        }
    }
    else{
        frameTime = 0;
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

