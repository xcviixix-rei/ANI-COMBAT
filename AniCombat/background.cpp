#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "gameHeader.h"
#include "background.h"

using namespace std;

BG :: BG(){
    BGMusic = loadSong("background/#themeMusic/lobbyMusic2.mp3");
    if( Mix_PlayingMusic() == 0 )
    {
        Mix_PlayMusic( BGMusic, -1 );
    }
    else
    {
        if( Mix_PausedMusic() == 1 )
        {
            Mix_ResumeMusic();
        }
    }
    cloudTime = SDL_GetTicks();
}

void BG :: loadBG(SDL_Renderer* renderer){
    int rate;
    string pathFirst = "background/jumpPlace/";
    string pathLast = ".png";
    background = loadTexture("background/backgroundLayer.png", renderer);
    ground = loadTexture("background/ground.png", renderer);
    stage = loadTexture("background/stage.png", renderer);
    cloud = loadTexture("background/cloud.png", renderer);
    jump[0] = loadTexture("background/jumpPlace/0.png", renderer);
    jump[1] = loadTexture("background/jumpPlace/1.png", renderer);
    jump[2] = loadTexture("background/jumpPlace/2.png", renderer);
    jump[3] = loadTexture("background/jumpPlace/1.png", renderer);
    jump[4] = loadTexture("background/jumpPlace/2.png", renderer);

    SDL_QueryTexture(stage, NULL, NULL, &stagePos.w, &stagePos.h);
    rate = screenW / stagePos.w;
    stagePos.w = screenW;
    stagePos.h *= rate;
    stagePos.x = 0;
    stagePos.y = screenH - stagePos.h;

    SDL_QueryTexture(ground, NULL, NULL, &groundPos.w, &groundPos.h);
    groundPos.w = screenW;
    groundPos.x = 0;
    groundPos.y = screenH - groundPos.h;

    SDL_QueryTexture(cloud, NULL, NULL, &cloudPos.w, NULL);
    cloudPos.h = 175;
    cloudPos.x = 0;
    cloudPos.y = 100;

    SDL_QueryTexture(jump[0],NULL, NULL, NULL, &jumpPlacePos[0].h);
    jumpPlacePos[0].w = 560;
    jumpPlacePos[0].x = (screenW - jumpPlacePos[0].w) / 2;
    jumpPlacePos[0].y = 420;

    SDL_QueryTexture(jump[1],NULL, NULL, NULL, &jumpPlacePos[1].h);
    jumpPlacePos[1].w = 120;
    jumpPlacePos[1].x = 0;
    jumpPlacePos[1].y = 534;

    jumpPlacePos[2] = jumpPlacePos[1];
    jumpPlacePos[2].x = screenW - jumpPlacePos[2].w;

    SDL_QueryTexture(jump[3],NULL, NULL, NULL, &jumpPlacePos[3].h);
    jumpPlacePos[3].w = 120;
    jumpPlacePos[3].x = 0;
    jumpPlacePos[3].y = 320;

    jumpPlacePos[4] = jumpPlacePos[3];
    jumpPlacePos[4].x = screenW - jumpPlacePos[4].w;
}

void BG :: renderCloud(SDL_Renderer* renderer){
    SDL_Rect cloudPos1, cloudPos2;

    cloudPos1.w = cloudPos2.w = screenW;
    cloudPos1.h = cloudPos2.h = cloudPos.h;
    cloudPos2.x = cloudPos.x;
    cloudPos1.x = cloudPos2.x - screenW;
    cloudPos1.y = cloudPos2.y = cloudPos.y;

    SDL_RenderCopy(renderer, cloud, NULL, &cloudPos1);
    SDL_RenderCopy(renderer, cloud, NULL, &cloudPos2);

    if(SDL_GetTicks() - cloudTime >= 30){
        cloudPos.x += cloudVelo;
        cloudTime = SDL_GetTicks();
    }
    if(cloudPos.x > screenW){
        cloudPos.x = 0;
    }
}

void BG :: renderJumpPlace(SDL_Renderer* renderer)
{
    SDL_RenderCopy(renderer, jump[0], NULL, &jumpPlacePos[0]);
    SDL_RenderCopy(renderer, jump[1], NULL, &jumpPlacePos[1]);
    SDL_RenderCopy(renderer, jump[2], NULL, &jumpPlacePos[2]);
    SDL_RenderCopy(renderer, jump[3], NULL, &jumpPlacePos[3]);
    SDL_RenderCopy(renderer, jump[4], NULL, &jumpPlacePos[4]);
}

void BG :: render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, background, NULL, NULL);
    renderCloud(renderer);
    SDL_RenderCopy(renderer, stage, NULL, &stagePos);
    SDL_RenderCopy(renderer, ground, NULL, &groundPos);
    renderJumpPlace(renderer);
}
