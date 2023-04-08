#include "gameHeader.h"

using namespace std;

class statusBar1
{
    public:
        static const int maxHPBarWidth = 250;

        statusBar1(int healthPoint, SDL_Renderer* renderer);

        int maxHP, currentHP;

        SDL_Texture *healthBar, *statusBar, *lostHPBar, *blankHPBar;
        SDL_Rect healthBarPos, statusBarPos, lostHPBarPos, blankHPBarPos;

        void updateHP(int healthPoint);
        void renderStatus(SDL_Renderer* renderer);

        Uint32 updateHPLostTime;

        ~statusBar1() {};
};
