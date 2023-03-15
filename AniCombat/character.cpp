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
    sheetW = 0;

    charRect.x = charRect.y = 0;

    leftRight = 2;

    collider.w = char_width;
    collider.h = char_height;

    veloX = 0;
    veloY = 0;

    charPos.w = 70;
    charPos.h = 84;
    charPos.x = 50;
}

void CRT :: initPosition(BG background){
    charPos.y = background.groundPos.y - charPos.h;
}

void CRT :: handleEvent(SDL_Event &e)
{
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                veloX -= char_velo;
                charStat = "run";
                leftRight = 1;
                break;

            case SDLK_d:
                veloX += char_velo;
                charStat = "run";
                leftRight = 2;
                break;
        }
    }

    else if( e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch( e.key.keysym.sym )
        {
            case SDLK_a:
                veloX += char_velo;
                charStat = charStat.empty();
                break;

            case SDLK_d:
                veloX -= char_velo;
                charStat = charStat.empty();
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
	collider.y = charPos.y;

    if( ( charPos.y < 0 ) || ( charPos.y + char_height > SCREEN_HEIGHT - 27 )  )
    {
        charPos.y -= veloY;
		collider.y = charPos.y;
		veloY = 0;
    }
}

void CRT :: loadChar(SDL_Renderer* renderer)
{
    charMotion = NULL;
    if( veloX == 0 && veloY == 0){
        if(leftRight == 1){
            charMotion = loadTexture("character/Naruto/standLeft.png", renderer);
                SDL_QueryTexture(charMotion, NULL, NULL, &sheetW, &charRect.h );
                charRect.w = sheetW / 4;
        }
        else if(leftRight == 2){
            charMotion = loadTexture("character/Naruto/standRight.png", renderer);
                SDL_QueryTexture(charMotion, NULL, NULL, &sheetW, &charRect.h );
                charRect.w = sheetW / 4;
        }
    }
    else if(veloX != 0 && veloY == 0){
        if(veloX < 0){
            charMotion = loadTexture("character/Naruto/runLeft.png", renderer);
            SDL_QueryTexture(charMotion, NULL, NULL, &sheetW, &charRect.h );
            charRect.w = sheetW / 8;
        }
        else if(veloX > 0){
            charMotion = loadTexture("character/Naruto/runRight.png", renderer);
            SDL_QueryTexture(charMotion, NULL, NULL, &sheetW, &charRect.h );
            charRect.w = sheetW / 8;
        }
    }
}

void CRT::render(SDL_Renderer* renderer)
{
    loadChar(renderer);

    SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);

    if(frameTime == 10){
        charRect.x += charRect.w;
        if(charRect.x >= sheetW){
            charRect.x = 0;
        }
        frameTime = 0;
    }
    if(veloX == 0 && veloY == 0) SDL_Delay(10);
    frameTime ++;
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

