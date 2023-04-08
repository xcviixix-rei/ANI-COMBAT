#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "background.h"
#include "gameHeader.h"

using namespace std;

enum characterStatus
{
    stand,
    run,
    jumpUp,
    fallDown,
    normalAttack,
    throwShuriken,
    getsugaTenshou,
    takeDamage,
    die
};

class CRT
{
    public:
        static const int char_velo = 8;
        static const int damage = 25;

        CRT() {};

        SDL_Rect charRect, charPos;

        SDL_Texture* charTexture;
        vector <SDL_Texture*> charIMG;

        Mix_Chunk* sfx;

        int char_width, char_height;
        int healthPoints;
        int takeDamageCount;
        int veloX, veloY;
        int tmpVelo;
        int previousVeloX;
        int previousVeloY;
        int w, h;
        int jumpCurrentHeight;
        int direction;
        // 1 la left, 2 la right
        vector <int> sheetW, sheetH;

        BG background;

        characterStatus charStat, previousCharStat;

        bool leftBeenPressed, rightBeenPressed;
        bool skillCond, normalAttackCond, throwingObjectCond;
        bool takingDamage, isDeath;
        bool enemyHPDecreased;

        Uint32 startTime, frameTime;
        Uint32 jumpTime, normalAttackTime, throwingObjectTime;
        Uint32 takingDamageTime;

        void loadSfx();

        void move();
        void render(SDL_Renderer* renderer);

        void checkJumpPlace();

        virtual void loadChar() {};
        virtual void renderSkill(SDL_Renderer* renderer) {};
/*
        virtual void initPosition();
        virtual void loadIMG(SDL_Renderer* renderer);
        virtual void handleEvent(SDL_Event e);
        virtual void move( SDL_Renderer* renderer);
*/
        ~CRT() {};
};
