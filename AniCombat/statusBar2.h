#include "gameHeader.h"

using namespace std;

class statusBar2
{
    public:
        static const int screenW = 960;
        static const int maxHPBarWidth = 132;

        statusBar2(int healthPoint, SDL_Renderer* renderer);

        int maxHP, currentHP;

        SDL_Texture *healthBar, *statusBar, *lostHPBar;
        SDL_Rect healthBarPos, statusBarPos, lostHPBarPos;

        void updateHP(int healthPoint);
        void renderStatus(SDL_Renderer* renderer);

        Uint32 updateHPLostTime;

        ~statusBar2() {};
};

