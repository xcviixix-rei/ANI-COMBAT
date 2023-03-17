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
        static const int char_velo = 4;
        static const int jumpHeightMax = 125;

        CRT();

        SDL_Rect collider, charRect, charPos;

        SDL_Texture* charMotion;

        SDL_Texture* charIMG[10];

        Mix_Chunk* sfx;

        void initPosition(BG background);

        void loadIMG(SDL_Renderer* renderer);

        void handleEvent( SDL_Event& e);

        void move( const int SCREEN_WIDTH, const int SCREEN_HEIGHT );

        void loadChar();

        void render(SDL_Renderer* renderer, BG &background);

        void renderSkill(SDL_Renderer* renderer, BG &background);

    private:

        Uint32 startTime;

        string charStat;

        int direction;
        // 1 la left, 2 la right

        bool skillCond;

        int frameNum, frameTime;

        vector <int> sheetW, sheetH;
        int w, h;

        int veloX, veloY;
        int jumpCurrentHeight;

        SDL_Texture* charTexture;

};

bool checkCollision( SDL_Rect a, SDL_Rect b );
