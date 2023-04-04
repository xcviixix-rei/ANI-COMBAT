#include "player.h"

using namespace std;

void CRT :: move()
{
    if(charStat != previousCharStat) charRect.x = 0;

    if(SDL_GetTicks() - startTime >= 5){

        startTime = SDL_GetTicks();

        charPos.x += veloX;

        if( ( charPos.x < 0 ) || ( charPos.x + char_width > background.screenW ) )
        {
            charPos.x -= veloX;
        }

        charPos.y += veloY;

        if(charStat == jumpUp || charStat == fallDown){
            if(SDL_GetTicks() - jumpTime >= 60){
                veloY += 2;
                jumpTime = SDL_GetTicks();
            }
        }

        if(charPos.y < jumpCurrentHeight){
            if(veloY > 0)
            {
                charStat = fallDown;
            }
            else if(veloY <= 0)
            {
                charStat = jumpUp;
            }
        }

        if( charPos.y > background.groundPos.y - charPos.h + 16 )
        {
            charPos.y = background.groundPos.y - charPos.h + 16 ;
            veloY = 0;
            jumpTime = SDL_GetTicks();
        }

        checkJumpPlace();

        if(veloY > 0){
            previousVeloY = veloY;
        }
        if(previousVeloY > 0 && veloY == 0){
            previousVeloY = 0;
            jumpCurrentHeight = charPos.y;
            jumpTime = SDL_GetTicks();
            charRect.x = 0;
            charStat = stand;
            frameTime = SDL_GetTicks();
        }
    }
}

void CRT :: render(SDL_Renderer* renderer)
{
    loadChar();

    if(skillCond == false){
        if(charStat == stand){
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 100){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= sheetW[0]){
                charRect.x = 0;
            }
            jumpCurrentHeight = charPos.y;
        }
        else if(charStat == run){
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 80){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= sheetW[1]){
                charRect.x = 0;
            }
            jumpCurrentHeight = charPos.y;
            if(veloX == 0) charStat = stand;
        }
        else if(charStat == jumpUp){
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 80){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= sheetW[2]){
                charRect.x = 0;
            }
        }
        else if(charStat == fallDown){
            SDL_RenderCopy(renderer, charMotion, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 80){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= sheetW[3]){
                charRect.x = 0;
            }
        }
    }
    else if(skillCond){
        renderSkill(renderer);
    }
    if(veloY == 0 && charPos.y == jumpCurrentHeight && veloX != 0) charStat = run;
    previousCharStat = charStat;
}

void CRT :: checkJumpPlace()
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
            charStat = fallDown;
            jumpTime = SDL_GetTicks();
            jumpCurrentHeight = background.groundPos.y - charPos.h + 16;
        }
    }
}

