#include"player.h"

using namespace std;

#pragma once

class player1 : public CRT
{
    public:
        player1(BG background);

        void initplayer1();
        void loadChar();
        void loadIMG(SDL_Renderer* renderer);
        void handleEvent(SDL_Event &e);
        void renderSkill(SDL_Renderer* renderer);

        ~player1() {};
};

