#pragma once

#include"player.h"

using namespace std;

class player2 : public CRT
{
    public:
        player2(BG background);

        SDL_Rect player2Body;

        Uint32 hackUpTime;

        void initplayer2();
        void loadChar();
        void loadIMG(SDL_Renderer* renderer);
        void handleEvent(SDL_Event &e);
        void renderSkill(SDL_Renderer* renderer);

        ~player2() {};
};
