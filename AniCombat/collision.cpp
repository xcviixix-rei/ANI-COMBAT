#include "collision.h"

using namespace std;


void collisionBetweenPlayer(player1 &plr1, player2 &plr2)
{
    if(plr2.healthPoints > 0 && plr1.healthPoints <= 0){
        plr1.charStat = die;
        if(plr2.waitToPose){
            plr2.waitTimeToPose = SDL_GetTicks();
            plr2.waitToPose = false;
        }
    }
    else if(plr1.healthPoints > 0 && plr2.healthPoints <= 0){
        plr2.charStat = die;
        if(plr1.waitToPose){
            plr1.waitTimeToPose = SDL_GetTicks();
            plr1.waitToPose = false;
        }
    }
    if( checkCollision(plr2.player2Body, plr1.charPos) && checkIfAFacingB(plr2.player2Body, plr1.charPos, plr2.direction, plr1.direction) && plr2.skillCond)
    {
        if(!checkIfAFacingB(plr1.charPos, plr2.player2Body, plr1.direction, plr2.direction)){
            if(plr1.direction == 1) plr1.direction = 2;
            else if(plr1.direction == 2) plr1.direction = 1;
        }
        plr1.charStat = takeDamage;
        plr1.skillCond = false;
        plr1.veloX = 0;
        plr1.veloY = 2;
        plr1.leftBeenPressed = plr1.rightBeenPressed = false;
        if(plr2.enemyHPDecreased && plr1.healthPoints > 0){
            if(plr1.direction == 1){
                plr1.charPos.x += 30;
                plr2.charPos.x += 20;
            }
            else if(plr1.direction == 2){
                plr1.charPos.x -= 30;
                plr2.charPos.x -= 20;
            }
            if(plr2.charStat == normalAttack){
                plr1.healthPoints -= plr2.damage;
                plr1.takingDamageTime = 200;
            }
            else if(plr2.charStat == hackUp){
                plr1.healthPoints -= 2 * plr2.damage;
                plr1.takingDamageTime = 500;
            }
            plr1.timeSinceTakenDamage = SDL_GetTicks();
            plr2.enemyHPDecreased = false;
            plr1.takeDamageCount ++;
        }
    }
    else if( checkCollision(plr1.charPos, plr2.player2Body) && checkIfAFacingB(plr1.charPos, plr2.player2Body, plr1.direction, plr2.direction) && plr1.skillCond)
    {
        if(!checkIfAFacingB(plr2.player2Body, plr1.charPos, plr2.direction, plr1.direction)){
            if(plr2.direction == 1) plr2.direction = 2;
            else if(plr2.direction == 2) plr2.direction = 1;
        }
        plr2.charStat = takeDamage;
        plr2.skillCond = false;
        plr2.veloX = 0;
        plr2.veloY = 2;
        plr2.leftBeenPressed = plr2.rightBeenPressed = false;
        if(plr1.enemyHPDecreased && plr2.healthPoints > 0){
            if(plr2.direction == 1){
                plr2.charPos.x += 30;
                plr1.charPos.x += 20;
            }
            else if(plr2.direction == 2){
                plr2.charPos.x -= 30;
                plr1.charPos.x -= 20;
            }
            if(plr1.charStat == normalAttack){
                plr2.healthPoints -= 1.2 * plr1.damage;
                plr2.takingDamageTime = 200;
            }
            else if(plr1.charStat == kick){
                plr2.healthPoints -= 1.6 * plr1.damage;
                plr2.takingDamageTime = 500;
            }
            plr2.timeSinceTakenDamage = SDL_GetTicks();
            plr1.enemyHPDecreased = false;
            plr2.takeDamageCount ++;
        }
    }
}

bool checkCollision(SDL_Rect a, SDL_Rect b)
{
    if( a.x + a.w <= b.x )
    {
        return false;
    }

    if( a.x >= b.x + b.w )
    {
        return false;
    }

    if( a.y + a.h <= b.y )
    {
        return false;
    }

    if( a.y >= b.y + b.h)
    {
        return false;
    }

    return true;
}

bool checkIfAFacingB(SDL_Rect a, SDL_Rect b, int aDirection, int bDirection)
{
    if( aDirection == 1 && a.x >= b.x)
    {
        return true;
    }
    if( aDirection == 2 && a.x <= b.x)
    {
        return true;
    }
    return false;
}
