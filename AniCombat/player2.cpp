#include "player2.h"

using namespace std;

player2 :: player2(BG bg)
{
    frameTime = SDL_GetTicks();
    startTime = SDL_GetTicks();

    charRect.x = charRect.y = 0;

    previousCharStat = charStat = stand;

    leftBeenPressed = rightBeenPressed = false;

    skillCond = false;
    throwingObjectCond = false;

    waitToPose = true;

    w = h = 0;

    veloX = 0;
    veloY = 0;

    jumpTime = SDL_GetTicks();
    hackUpTime = SDL_GetTicks();
    normalAttackTime = SDL_GetTicks();
    throwingObjectTime = SDL_GetTicks();

    background = bg;

    healthPoints = 300;
    takeDamageCount = 0;

    char_width = 100;
    char_height = 72;
}

void player2 :: initplayer2()
{
    direction = 1;
    charPos.w = char_width;
    charPos.h = char_height;
    charPos.x = background.screenW - char_width - 50;
    charPos.y = background.groundPos.y - charPos.h + 4;
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

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/takeDamageLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[12]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/takeDamageRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[13]
    SDL_QueryTexture(charIMG[12], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //6

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/winLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[14]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/winRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[15]
    SDL_QueryTexture(charIMG[14], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //7

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/dieLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[16]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/dieRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[17]
    SDL_QueryTexture(charIMG[16], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //8

    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/hackUpLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[18]
    charTexture = loadTexture("character/Ichigo/ichigoSpriteSheet/hackUpRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[19]
    SDL_QueryTexture(charIMG[18], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //9
}
void player2 :: handleEvent(SDL_Event &e)
{
    if(charStat != die && charStat != win && charStat != takeDamage && !skillCond){
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_LEFT:
                    leftBeenPressed = true;
                    charRect.x = 0;
                    veloX -= char_velo;
                    direction = 1;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = run;
                    }
                    break;

                case SDLK_RIGHT:
                    rightBeenPressed = true;
                    charRect.x = 0;
                    veloX += char_velo;
                    direction = 2;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = run;
                    }
                    break;

                case SDLK_UP:
                    if(charPos.y == jumpCurrentHeight){
                        if(direction == 1) charPos.x += 25;
                        charRect.x = 0;
                        charStat = jumpUp;
                        veloY = - 1.5 * char_velo;
                        jumpTime = SDL_GetTicks();
                    }
                    break;

                case SDLK_i:
                    if((SDL_GetTicks() - normalAttackTime >= 80) && (charPos.y == jumpCurrentHeight)){
                        charRect.x = 0;
                        charStat = normalAttack;
                        frameTime = SDL_GetTicks();
                        tmpVelo = veloX;
                        veloX = 0;
                        skillCond = true;
                        enemyHPDecreased = true;
                    }
                    break;

                case SDLK_k:
                    if((SDL_GetTicks() - hackUpTime >= 250) && (charPos.y == jumpCurrentHeight)){
                        charRect.x = 0;
                        charStat = hackUp;
                        frameTime = SDL_GetTicks();
                        tmpVelo = veloX;
                        veloX = 0;
                        skillCond = true;
                        enemyHPDecreased = true;
                    }
                    break;

    /*            case SDLK_o:
                    if(SDL_GetTicks() - throwingObjectTime >= 500) && (charPos.y == jumpCurrentHeight)){
                        charRect.x = 0;
                        charStat = getsugaTenshou;
                        frameTime = SDL_GetTicks();
                        tmpVelo = veloX;
                        veloX = 0;
                        skillCond = true;
                        throwingObjectCond = true;
                    }
                    break; */
            }
        }

        else if( e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_LEFT:
                    if(leftBeenPressed){
                        charRect.x = 0;
                        veloX += char_velo;
                        leftBeenPressed = false;
                        if(charPos.y == jumpCurrentHeight){
                            charStat = stand;
                        }
                    }
                    break;

                case SDLK_RIGHT:
                    if(rightBeenPressed){
                        charRect.x = 0;
                        veloX -= char_velo;
                        rightBeenPressed = false;
                        if(charPos.y == jumpCurrentHeight){
                            charStat = stand;
                        }
                    }
                    break;
            }
        }
    }
    else if(skillCond){
        if( e.type == SDL_KEYUP && e.key.repeat == 0)
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_LEFT:
                    if(leftBeenPressed){
                        tmpVelo = 0;
                        veloX = 0;
                        leftBeenPressed = false;
                    }
                    break;

                case SDLK_RIGHT:
                    if(rightBeenPressed){
                        tmpVelo = 0;
                        veloX = 0;
                        rightBeenPressed = false;
                    }
                    break;
            }
        }
    }
}

void player2 :: loadChar()
{
    charTexture = nullptr;

    charPos.w = char_width;
    charPos.h = char_height;
    if(previousCharStat != charStat){
        charRect.x = 0;
        if(previousCharStat == fallDown && previousVeloY > 2 && direction == 1){
            charPos.x -= 25;
        }
    }
    if(veloY == 0 && charPos.y == jumpCurrentHeight && veloX != 0 && !skillCond){
        charStat = run;
    }
    if(healthPoints <= 0){
        charStat = die;
    }
    if(SDL_GetTicks() - waitTimeToPose > 2000 && !waitToPose) charStat = win;

    player2Body = charPos;

    if(charStat == stand){
        if(direction == 1){
            player2Body.w = 0.6 * charPos.w;
            player2Body.x = charPos.x + charPos.w - player2Body.w;

            charTexture = charIMG[0];
            charRect.w = sheetW[0] / 4;
            charRect.h = sheetH[0];
        }
        else if(direction == 2){
            player2Body.w = 0.6 * charPos.w;
            player2Body.x = charPos.x;

            charTexture = charIMG[1];
            charRect.w = sheetW[0] / 4;
            charRect.h = sheetH[0];
        }
    }
    if(charStat == run){
        charPos.w = 110;
        if(veloX < 0){
            charTexture = charIMG[2];
            charRect.w = sheetW[1] / 8;
            charRect.h = sheetH[1];
            direction = 1;
        }
        else if(veloX > 0){
            charTexture = charIMG[3];
            charRect.w = sheetW[1] / 8;
            charRect.h = sheetH[1];
            direction = 2;
        }
    }
    if(charStat == jumpUp){
        charPos.w = 72;
        if(direction == 1){
            charTexture = charIMG[4];
            charRect.w = sheetW[2] / 2;
            charRect.h = sheetH[2];
        }
        else if(direction == 2){
            charTexture = charIMG[5];
            charRect.w = sheetW[2] / 2;
            charRect.h = sheetH[2];
        }
    }
    if(charStat == fallDown){
        charPos.w = 72;
        if(direction == 1){
            charTexture = charIMG[6];
            charRect.w = sheetW[3] / 2;
            charRect.h = sheetH[3];
        }
        else if(direction == 2){
            charTexture = charIMG[7];
            charRect.w = sheetW[3] / 2;
            charRect.h = sheetH[3];
        }
    }
    if(charStat == normalAttack){
        charPos.w = 142;
        if(direction == 1){
            charTexture = charIMG[8];
            charRect.w = sheetW[4] / 6;
            charRect.h = sheetH[4];
        }
        else if(direction == 2){
            player2Body.w = 0.75 * charPos.w;

            charTexture = charIMG[9];
            charRect.w = sheetW[4] / 6;
            charRect.h = sheetH[4];
        }
    }
    if(charStat == getsugaTenshou){
        charPos.w = 155;
        if(direction == 1){
            charTexture = charIMG[10];
            charRect.w = sheetW[5] / 8;
            charRect.h = sheetH[5];
        }
        else if(direction == 2){
            charTexture = charIMG[11];
            charRect.w = sheetW[5] / 8;
            charRect.h = sheetH[5];
        }
    }
    if(charStat == takeDamage){
        if(direction == 1){
            charTexture = charIMG[12];
            charRect.w = sheetW[6] / 4;
            charRect.h = sheetH[6];
        }
        else if(direction == 2){
            charTexture = charIMG[13];
            charRect.w = sheetW[6] / 4;
            charRect.h = sheetH[6];
        }
    }
    if(charStat == win){
        charPos.w = 100;
        if(direction == 1){
            charTexture = charIMG[14];
            charRect.w = sheetW[7] / 6;
            charRect.h = sheetH[7];
        }
        else if(direction == 2){
            charTexture = charIMG[15];
            charRect.w = sheetW[7] / 6;
            charRect.h = sheetH[7];
        }
    }
    if(charStat == die){
        charPos.w = 80;
        charPos.y = jumpCurrentHeight - 30;
        charPos.h = char_height + 30;
        if(direction == 1){
            charTexture = charIMG[16];
            charRect.w = sheetW[8] / 7;
            charRect.h = sheetH[8];
        }
        else if(direction == 2){
            charTexture = charIMG[17];
            charRect.w = sheetW[8] / 7;
            charRect.h = sheetH[8];
        }
    }
    if(charStat == hackUp){
        charPos.w = 140;
        if(direction == 1){
            charTexture = charIMG[18];
            charRect.w = sheetW[9] / 7;
            charRect.h = sheetH[9];
        }
        else if(direction == 2){
            charTexture = charIMG[19];
            charRect.w = sheetW[9] / 7;
            charRect.h = sheetH[9];
        }
    }
}

void player2 :: renderSkill(SDL_Renderer* renderer)
{
    if(charStat == normalAttack ){
        if(direction == 2){
            charPos.x -= 45;
        }
        SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
        if(SDL_GetTicks() - frameTime >= 60){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[4]){
            charRect.x = 0;
            veloX = tmpVelo;
            tmpVelo = NULL;
            skillCond = false;
            enemyHPDecreased = false;
            charStat = stand;
        }
        normalAttackTime = SDL_GetTicks();
        if(direction == 2){
            charPos.x += 45;
        }
    }
    if(charStat == hackUp ){
        veloX = 0;
        veloY = 0;
        charPos.y -= 80;
        charPos.h += 80;
        if(direction == 1){
            charPos.x -= 30;
        }
        else if(direction == 2){
            charPos.x -= 20;
        }
        if(charRect.x < 2 * charRect.w){
            if(direction == 1){
                veloX = - 1.75 * char_velo;
            }
            else if(direction == 2){
                veloX = 1.75 * char_velo;
            }
        }
        SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
        if(SDL_GetTicks() - frameTime >= 55){
            charRect.x += charRect.w;
            frameTime = SDL_GetTicks();
        }
        if(charRect.x >= sheetW[9]){
            charRect.x = 0;
            veloX = tmpVelo;
            tmpVelo = NULL;
            skillCond = false;
            enemyHPDecreased = false;
            charStat = fallDown;
        }
        hackUpTime = SDL_GetTicks();
        charPos.y += 80;
        charPos.h -= 80;
        if(direction == 1) charPos.x += 30;
        else if(direction == 2) charPos.x += 20;
    }
/*
    if(charStat == getsugaTenshou){
        if(throwingObjectCond){
            if(direction == 1) charPos.x -= 20;
            else if(direction == 2) charPos.x -= 30;
            SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 40){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= sheetW[5]){
                charRect.x = 0;
                veloX = tmpVelo;
                tmpVelo = NULL;
                skillCond = false;
                throwingObjectCond = false;
                charStat = stand;
            }
            throwingObjectTime = SDL_GetTicks();
            if(direction == 1) charPos.x += 20;
            else if(direction == 2) charPos.x += 30;
        }
    }
*/
}
