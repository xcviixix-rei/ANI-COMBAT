#include "player1.h"
#include "player2.h"

using namespace std;

void collisionBetweenPlayer( player1 &plr1, player2 &plr2);

bool checkCollision(SDL_Rect a, SDL_Rect b);

bool checkIfAFacingB(SDL_Rect a, SDL_Rect b, int aDirection, int bDirection);
