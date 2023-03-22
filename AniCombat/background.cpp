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
    cloudTime = 0;
}

void BG :: loadBG(SDL_Renderer* renderer){
    int rate;
    string pathFirst = "background/jumpPlace/";
    string pathLast = ".png";
    background = loadTexture("background/backgroundLayer.png", renderer);
    ground = loadTexture("background/ground.png", renderer);
    stage = loadTexture("background/stage.png", renderer);
    cloud = loadTexture("background/cloud.png", renderer);
    for(int i = 0; i < 5; i++){
        char x = i + 48;
        string path =  pathFirst + x + pathLast;
        jump[i] = loadTexture(path, renderer);
    }

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

    if(cloudTime == 3){
        cloudPos.x += cloudVelo;
        cloudTime = 0;
    }
    cloudTime ++;
    if(cloudPos.x > screenW){
        cloudPos.x = 0;
    }
}

void BG :: render(SDL_Renderer* renderer){
    SDL_RenderCopy(renderer, background, NULL, NULL);
    renderCloud(renderer);
    SDL_RenderCopy(renderer, stage, NULL, &stagePos);
    SDL_RenderCopy(renderer, ground, NULL, &groundPos);
}
