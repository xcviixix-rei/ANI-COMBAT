#include "gameHeader.h"

using namespace std;

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, const string WINDOW_TITLE, SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING ) < 0)
        logSDLError(cout, "SDL_Init", true);

    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    if (window == nullptr) logSDLError(cout, "CreateWindow", true);



    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                  SDL_RENDERER_PRESENTVSYNC);

    if (renderer == nullptr) logSDLError(cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    if( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 2048) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
}



void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

Mix_Chunk* loadSound (string path)
{
    Mix_Chunk* newSound = nullptr;
    newSound = Mix_LoadWAV(path.c_str());
    if(newSound == nullptr)
    {
        cout << "Unable to load sound " << path << "Mix_Chunk Error: " << Mix_GetError() << endl;
    }
    return newSound;
}

Mix_Music* loadSong (string path)
{
    Mix_Music* newSong = nullptr;
    newSong = Mix_LoadMUS(path.c_str());
    if(newSong == nullptr)
    {
        cout << "Unable to load song " << path << "Mix_Music Error: " << Mix_GetError() << endl;
    }
    return newSong;
}

SDL_Texture* loadTexture( string path, SDL_Renderer* renderer)
{
    SDL_Texture* newTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if( loadedSurface == nullptr )
    {
        cout << "Unable to load image " << path << " SDL_image Error: " << IMG_GetError() << endl;
    }
    else
    {
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface);
        if( newTexture == nullptr)
        {
            cout << "Unable to create texture from " << path << " SDL Error: " << SDL_GetError() << endl;
        }
        SDL_FreeSurface( loadedSurface);
    }
    return newTexture;
}
