#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "background.h"
#include "gameHeader.h"

using namespace std;

#pragma once

enum characterStatus
{
    stand,
    run,
    jumpUp,
    fallDown,
    normalAttack,
    throwShuriken,
    getsugaTenshou
};

enum objectType
{
    shuriken,
    airSlash
};

class CRT
{
    public:
        static const int char_velo = 8;
        static const int damage = 25;

        CRT() {};

        SDL_Rect charRect, charPos;

        SDL_Texture* charMotion;
        SDL_Texture* charTexture;
        vector <SDL_Texture*> charIMG;

        Mix_Chunk* sfx;

        int char_width, char_height;
        int healthPoints;
        int veloX, veloY;
        int tmpVelo;
        int previousVeloY;
        int w, h;
        int jumpCurrentHeight;
        int direction;
        // 1 la left, 2 la right
        vector <int> sheetW, sheetH;

        BG background;

        characterStatus charStat, previousCharStat;
        objectType objType;

        bool skillCond, normalAttackCond, throwingObjectCond;

        Uint32 startTime, frameTime;
        Uint32 jumpTime, normalAttackTime, throwingObjectTime;

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
