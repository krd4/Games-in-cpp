#pragma once
#include "SDL.h"
#include "Vector.h"

class Game 
{
public: 
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();
private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    bool mIsRunning;

    Vector2 mBallPos;
    int mWidth;
    int mHeight;
};