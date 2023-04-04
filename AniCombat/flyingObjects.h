#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include "background.h"
#include "player.h"

using namespace std;

#pragma once

class flyingObjects
{
    public:
        flyingObjects();
        flyingObjects( CRT &chrt, BG &bg );
        ~flyingObjects();

        SDL_Texture* object;
        SDL_Texture* objectIMG[10];
        SDL_Rect objectPos, objectRect;

        void loadObjectIMG(SDL_Renderer* renderer);
        void loadObject();

        void renderObject(SDL_Renderer* renderer);

        int flyingVelo;
        int w,h;
        vector <int> sheetW, sheetH;

        bool flyingTime;
        bool objectCond;

        Uint32 frameTime;

        CRT character;
        BG background;
};
