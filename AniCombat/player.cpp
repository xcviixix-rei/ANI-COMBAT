#include "player.h"

using namespace std;

void CRT :: move()
{
    if(SDL_GetTicks() - startTime >= 5){

        startTime = SDL_GetTicks();

        charPos.x += veloX;

        if( charPos.x < 0 ){
            charPos.x = 0;
        }
        else if ( charPos.x + charPos.w > background.screenW )
        {
            charPos.x = background.screenW - charPos.w;
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

        if( charPos.y > background.groundPos.y - charPos.h + 4 )
        {
            charPos.y = background.groundPos.y - charPos.h + 4 ;
            veloY = 0;
            jumpTime = SDL_GetTicks();
        }

        checkJumpPlace();
    }
}

void CRT :: render(SDL_Renderer* renderer)
{
    loadChar();

    if(charStat != previousCharStat){
        charRect.x = 0;
        previousCharStat = charStat;
    }
    if(charStat != takeDamage && charStat != die){
        if(!skillCond){
            if(charStat == stand){
                SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
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
                SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
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
                SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
                if(SDL_GetTicks() - frameTime >= 80){
                    charRect.x += charRect.w;
                    frameTime = SDL_GetTicks();
                }
                if(charRect.x >= sheetW[2]){
                    charRect.x = 0;
                }
            }
            else if(charStat == fallDown){
                SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
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
    }
    else if(charStat != die && charStat == takeDamage){
        charRect.x = (takeDamageCount - 1) * charRect.w;
        SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
        if(SDL_GetTicks() - takingDamageTime >= 200){
            charStat = stand;
            charRect.x = 0;
        }
        if(takeDamageCount > 4) takeDamageCount = 1;
    }
    else if(charStat == die){
        SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
        if(charRect.x < sheetW[8] - charRect.w){
            if(SDL_GetTicks() - frameTime >= 100){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(direction == 1) charPos.x += 4;
            else if(direction == 2) charPos.x -= 4;
        }
    }
    if(charStat == win){
        SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
        if(SDL_GetTicks() - frameTime >= 120){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[7]){
            charRect.x = 3 * charRect.w;
        }
    }
    previousCharStat = charStat;
}

void CRT :: checkJumpPlace()
{
    if( (charPos.y + char_height >= background.jumpPlacePos[4].y - 2 ) && (charPos.y + char_height <= background.jumpPlacePos[4].y + 10) && (charPos.x + char_width / 3 >= background.jumpPlacePos[4].x ) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[4].y - char_height + 4;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[3].y - 2) && (charPos.y + char_height <= background.jumpPlacePos[3].y + 10) && (charPos.x + char_width / 3 <= background.jumpPlacePos[3].w ) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[3].y - char_height + 4;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[2].y - 2) && (charPos.y + char_height <= background.jumpPlacePos[2].y + 10) && (charPos.x + char_width / 3 >= background.jumpPlacePos[2].x ) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[2].y - char_height + 4;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[1].y - 2) && (charPos.y + char_height <= background.jumpPlacePos[1].y + 10) && (charPos.x + char_width / 3 <= background.jumpPlacePos[1].w ) ){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[1].y - char_height + 4;
        }
    }
    else if( (charPos.y + char_height >= background.jumpPlacePos[0].y - 4) && (charPos.y + char_height <= background.jumpPlacePos[0].y + 12) && (charPos.x + char_width / 3 >= background.jumpPlacePos[0].x ) && (charPos.x + char_width / 3 <= background.jumpPlacePos[0].x + background.jumpPlacePos[0].w )){
        if(veloY > 0){
            veloY = 0;
            jumpTime = SDL_GetTicks();
            charPos.y = background.jumpPlacePos[0].y - char_height + 4;
        }
    }
    else if( ( (charPos.y + char_height == background.jumpPlacePos[4].y + 4) && (charPos.x + char_width / 3 < background.jumpPlacePos[4].x ) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[3].y + 4) && (charPos.x + char_width / 3 > background.jumpPlacePos[3].w ) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[2].y + 4) && (charPos.x + char_width / 3 < background.jumpPlacePos[2].x ) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[1].y + 4) && (charPos.x + char_width / 3 > background.jumpPlacePos[1].w ) ) ||
             ( (charPos.y + char_height == background.jumpPlacePos[0].y + 4) && ((charPos.x + char_width / 3 < background.jumpPlacePos[0].x ) || (charPos.x + char_width / 3 > background.jumpPlacePos[0].x + background.jumpPlacePos[0].w)))){
        if(veloY == 0){
            veloY = 2;
            charStat = fallDown;
            jumpTime = SDL_GetTicks();
            jumpCurrentHeight = background.groundPos.y - charPos.h + 4;
        }
    }
    if(previousVeloX != veloX ){
        previousVeloX = veloX;
        charRect.x = 0;
        frameTime = SDL_GetTicks();
    }
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
    previousVeloX = veloX;
}

