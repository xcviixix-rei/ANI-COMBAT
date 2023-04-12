#include "gameHeader.h"

using namespace std;

class menu
{
    public:
        menu(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);

        int screenW, screenH;
        int optionsNumber, optionChoosen;
        int transVelo;
        int instructionDistance;
        int blinkTimes;

        bool menuIsRunning;
        bool doneTransition;
        bool menuToInstruction;

        SDL_Texture* menuTexture;

        SDL_Texture* play, *playChoosen, *instruction, *instructionChoosen;
        SDL_Rect playPos, instructionPos;

        SDL_Texture* instruction1, *instruction2;
        SDL_Rect instruction1Pos, instruction2Pos;

        SDL_Texture* pointArrowRight, *pointArrowLeft;
        SDL_Rect pointArrowRightPos, pointArrowLeftPos;

        SDL_Texture* instructionReturn;
        SDL_Rect instructionReturnPos, instructionReturnRect;

        SDL_Texture* buttonInstruction;
        SDL_Rect buttonInstructionPos, buttonInstructionRect;

        Mix_Music* menuMusic;

        Uint32 frameTime;
        Uint32 blinkingTime;

        void loadMenuIMG(SDL_Renderer* renderer);
        void handleEvent(SDL_Event &e);
        void render(SDL_Renderer* renderer);

        ~menu();
};
