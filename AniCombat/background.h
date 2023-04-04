#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "gameHeader.h"

using namespace std;

#pragma once
class BG
{
public:
    static const int screenW = 960;
    static const int screenH = 720;
    static const int cloudVelo = 1;

    BG();
    ~BG();

    void loadBG(SDL_Renderer* renderer);

    void renderCloud(SDL_Renderer* renderer);
    void renderJumpPlace(SDL_Renderer* renderer);
    void render(SDL_Renderer* renderer);

    SDL_Rect groundPos, stagePos, cloudPos;
    SDL_Rect jumpPlacePos[5];

    SDL_Texture* background, *ground, *stage, *cloud;
    SDL_Texture* jump[5];

private:
    Mix_Music* BGMusic;
    Uint32 cloudTime;

};
