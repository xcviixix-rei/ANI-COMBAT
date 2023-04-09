#include "player1.h"

using namespace std;

player1 :: player1(BG bg)
{
    frameTime = SDL_GetTicks();
    startTime = SDL_GetTicks();

    charRect.x = charRect.y = 0;

    previousCharStat = charStat = stand;

    leftBeenPressed = rightBeenPressed = false;

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

    healthPoints = 300;
    takeDamageCount = 0;

    char_width = 44;
    char_height = 72;
}

void player1 :: initplayer1()
{
    direction = 2;
    charPos.w = char_width;
    charPos.h = char_height;
    charPos.x = 50 ;
    charPos.y = background.groundPos.y - charPos.h + 4;
}

void player1 :: loadIMG(SDL_Renderer* renderer)
{
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/standLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[0]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/standRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[1]
    SDL_QueryTexture(charIMG[0], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //0

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/runLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[2]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/runRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[3]
    SDL_QueryTexture(charIMG[2], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //1

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/jumpUpLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[4]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/jumpUpRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[5]
    SDL_QueryTexture(charIMG[4], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //2

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/fallDownLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[6]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/fallDownRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[7]
    SDL_QueryTexture(charIMG[6], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //3

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/normalAttackLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[8]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/normalAttackRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[9]
    SDL_QueryTexture(charIMG[8], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //4

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/throwShurikenLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[10]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/throwShurikenRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[11]
    SDL_QueryTexture(charIMG[10], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //5

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/takeDamageLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[12]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/takeDamageRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[13]
    SDL_QueryTexture(charIMG[12], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //6

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/winLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[14]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/winRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[15]
    SDL_QueryTexture(charIMG[14], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //7

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/dieLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[16]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/dieRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[17]
    SDL_QueryTexture(charIMG[16], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //8

    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/kickLeft.png", renderer);
    charIMG.push_back(charTexture); // charIMG[18]
    charTexture = loadTexture("character/Naruto/narutoSpriteSheet/kickRight.png", renderer);
    charIMG.push_back(charTexture); // charIMG[19]
    SDL_QueryTexture(charIMG[18], NULL, NULL, &w, &h);
    sheetW.push_back(w); sheetH.push_back(h);
    //9

/*
    obj1.loadObjectIMG(renderer);
    obj2.loadObjectIMG(renderer);
    obj3.loadObjectIMG(renderer);
*/
}
void player1 :: handleEvent(SDL_Event &e)
{
    if(charStat != die && charStat != win && charStat != takeDamage && !skillCond){
        if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
        {
            switch( e.key.keysym.sym )
            {
                case SDLK_a:
                    leftBeenPressed = true;
                    charRect.x = 0;
                    veloX -= char_velo;
                    direction = 1;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = run;
                    }
                    break;

                case SDLK_d:
                    rightBeenPressed = true;
                    charRect.x = 0;
                    veloX += char_velo;
                    direction = 2;
                    if(charPos.y == jumpCurrentHeight){
                        charStat = run;
                    }
                    break;

                case SDLK_w:
                    if(charPos.y == jumpCurrentHeight){
                        charRect.x = 0;
                        charStat = jumpUp;
                        veloY = - 1.5 * char_velo;
                        jumpTime = SDL_GetTicks();
                    }
                    break;

                case SDLK_r:
                    if((SDL_GetTicks() - normalAttackTime >= 80) && (charPos.y == jumpCurrentHeight)){
                        charRect.x = 0;
                        charStat = normalAttack;
                        frameTime = SDL_GetTicks();
                        tmpVelo = veloX;
                        veloX = 0;
                        skillCond = true;
                        normalAttackCond = true;
                        enemyHPDecreased = true;
                    }
                    break;

                case SDLK_f:
                    if((SDL_GetTicks() - normalAttackTime >= 250) && (charPos.y == jumpCurrentHeight)){
                        charRect.x = 0;
                        charStat = kick;
                        frameTime = SDL_GetTicks();
                        tmpVelo = veloX;
                        veloX = 0;
                        skillCond = true;
                        kickCond = true;
                        enemyHPDecreased = true;
                        if(direction == 1) charPos.x -= 30;
                    }
                    break;

    /*            case SDLK_t:
                    if((SDL_GetTicks() - throwingObjectTime >= 500) && (charPos.y == jumpCurrentHeight)){
                        charRect.x = 0;
                        charStat = throwShuriken;
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
                case SDLK_a:
                    if(leftBeenPressed){
                        charRect.x = 0;
                        veloX += char_velo;
                        leftBeenPressed = false;
                        if(charPos.y == jumpCurrentHeight){
                            charStat = stand;
                        }
                    }
                    break;

                case SDLK_d:
                    if(rightBeenPressed){
                        charRect.x = 0;
                        veloX -= char_velo;
                        rightBeenPressed = false;
                        if(charPos.y == jumpCurrentHeight){
                            charStat = stand;
                        }
                    }
                    else if(skillCond && rightBeenPressed){
                        tmpVelo = 0;
                        veloX = 0;
                        rightBeenPressed = false;
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
                case SDLK_a:
                    if(leftBeenPressed){
                        tmpVelo = 0;
                        veloX = 0;
                        leftBeenPressed = false;
                    }
                    break;

                case SDLK_d:
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

void player1 :: loadChar()
{
    charTexture = nullptr;
    charPos.w = char_width;
    if(previousCharStat != charStat) charRect.x = 0;
    if(veloY == 0 && charPos.y == jumpCurrentHeight && veloX != 0 && !skillCond){
        charStat = run;
    }
    if(healthPoints <= 0){
        charStat = die;
    }
    if(charStat == stand){
        if(direction == 1){
            charTexture = charIMG[0];
            charRect.w = sheetW[0] / 4;
            charRect.h = sheetH[0];
        }
        else if(direction == 2){
            charTexture = charIMG[1];
            charRect.w = sheetW[0] / 4;
            charRect.h = sheetH[0];
        }
    }
    if(charStat == run){
        charPos.w = 50;
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
        charPos.w = 54;
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
        charPos.w = 54;
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
        charPos.w = 84;
        if(direction == 1){
            charTexture = charIMG[8];
            charRect.w = sheetW[4] / 5;
            charRect.h = sheetH[4];
        }
        else if(direction == 2){
            charTexture = charIMG[9];
            charRect.w = sheetW[4] / 5;
            charRect.h = sheetH[4];
        }
    }
    if(charStat == throwShuriken){
        if(direction == 1){
            charTexture = charIMG[10];
            charRect.w = sheetW[5] / 6;
            charRect.h = sheetH[5];
        }
        else if(direction == 2){
            charTexture = charIMG[11];
            charRect.w = sheetW[5] / 6;
            charRect.h = sheetH[5];
        }
    }
    if(charStat == takeDamage){
        charPos.w = 50;
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
        charPos.w = 40;
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
    if(charStat == kick){
        charPos.w = 80;
        if(direction == 1){
            charTexture = charIMG[18];
            charRect.w = sheetW[9] / 6;
            charRect.h = sheetH[9];
        }
        else if(direction == 2){
            charTexture = charIMG[19];
            charRect.w = sheetW[9] / 6;
            charRect.h = sheetH[9];
        }
    }
/*    obj1.loadObject();
    obj2.loadObject();
    obj3.loadObject();
*/
}

void player1 :: renderSkill(SDL_Renderer* renderer)
{
    if(charStat == normalAttack){
        if(normalAttackCond){
            if(direction == 1){
                charPos.x -= 32;
            }
            SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 50){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= sheetW[4]){
                charRect.x = 0;
                veloX = tmpVelo;
                tmpVelo = NULL;
                normalAttackCond = false;
                skillCond = false;
                enemyHPDecreased = false;
                charStat = stand;
            }
            normalAttackTime = SDL_GetTicks();
            if(direction == 1){
                charPos.x += 32;
            }
        }
    }
    if(charStat == kick ){
        if(kickCond){
            veloY = 0;
            if(direction == 1){
                veloX = - 1.75 * char_velo;
            }
            else if(direction == 2){
                veloX = 1.75 * char_velo;
            }
            SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 75){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            if(charRect.x >= 3 * charRect.w){
                veloX = tmpVelo;
                tmpVelo = NULL;
            }
            if(charRect.x >= sheetW[9]){
                charRect.x = 0;
                veloX = tmpVelo;
                tmpVelo = NULL;
                kickCond = false;
                skillCond = false;
                enemyHPDecreased = false;
                charStat = fallDown;
            }
            normalAttackTime = SDL_GetTicks();
        }
    }
    if(charStat == throwShuriken ){
        if(throwingObjectCond){
            SDL_RenderCopy(renderer, charTexture, &charRect, &charPos);
            if(SDL_GetTicks() - frameTime >= 20){
                charRect.x += charRect.w;
                frameTime = SDL_GetTicks();
            }
            /*if(charRect.x == 4 * charRect.w){
                if(obj1.objectCond) obj1.initObjectPosition(direction, charPos);
                if(obj2.objectCond && !obj1.objectCond) obj2.initObjectPosition(direction, charPos);
                if(obj3.objectCond && !obj2.objectCond) obj3.initObjectPosition(direction, charPos);
            }*/
            if(charRect.x >= sheetW[5]){
                charRect.x = 0;
                veloX = tmpVelo;
                tmpVelo = NULL;
                skillCond = false;
                throwingObjectCond = false;
                charStat = stand;
            }
            throwingObjectTime = SDL_GetTicks();
        }
    }
}
/*
void player1 :: renderObject(SDL_Renderer* renderer)
{
    obj1.renderObject(renderer);
    obj2.renderObject(renderer);
    obj3.renderObject(renderer);
}
*/
