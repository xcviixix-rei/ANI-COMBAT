#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "background.h"

using namespace std;

#pragma once
class CRT{
    public:

        static const int char_width = 80;
        static const int char_height = 96;
        static const int char_velo = 8;

        CRT();

        SDL_Rect charRect, charPos;
        SDL_Rect objectRect, objectPos;

        SDL_Texture* charMotion;
        SDL_Texture* object;

        SDL_Texture* charIMG[50];
        SDL_Texture* objectIMG[10];

        Mix_Chunk* sfx;

        void initPosition(BG background);

        void loadIMG(SDL_Renderer* renderer);

        void handleEvent( SDL_Event& e);

        void move( SDL_Renderer* renderer, const int SCREEN_WIDTH, const int SCREEN_HEIGHT, BG &background );

        void loadChar();
        void loadObject();

        void renderObjects(SDL_Renderer* renderer, BG background);
        void render(SDL_Renderer* renderer, BG &background);
        void renderSkill(SDL_Renderer* renderer, BG &background);

        void checkJumpPlace(SDL_Renderer* renderer, BG &background);

    private:

        int veloX, veloY;
        int previousVeloY;
        int w, h;
        int jumpCurrentHeight;
        int objectVelo;
        int shurikenVelo;
        int direction;
        // 1 la left, 2 la right
        vector <int> sheetW, sheetH, objectSheetW, objectSheetH;

        string charStat;
        string objectType;

        bool skillCond;
        bool objectCond;

        Uint32 startTime, frameTime, objectFrameTime;
        Uint32 jumpTime, normalAtkTime, throwShurikenTime, objectMoveTime;

        SDL_Texture* charTexture;
};

bool checkCollision( SDL_Rect a, SDL_Rect b );
