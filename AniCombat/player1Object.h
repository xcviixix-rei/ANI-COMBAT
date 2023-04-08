#pragma once

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "gameHeader.h"

using namespace std;

class player1Object
{
    public:
        player1Object();

        SDL_Texture* objectTexture;
        vector <SDL_Texture*> objectIMG;

        SDL_Rect objectPos, objectRect;
        SDL_Rect charPos;

        static const int screenW = 960;
        int flyingVelo;
        int objectWidth, objectHeight;
        int direction;
        int sheetW, sheetH;

        bool objectCond;

        Uint32 frameTime;

        void initObjectPosition(int drt, SDL_Rect characterPos);
        void loadObjectIMG(SDL_Renderer* renderer);
        void loadObject();

        void renderObject(SDL_Renderer* renderer);

        ~player1Object() {};
};
