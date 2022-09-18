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
    Vector2 mPaddlePos;
    Vector2 mBallVel;
    float mPaddleVel;
    int mPaddleDir;
    int mWidth;
    int mHeight;
    int paddleH;

    Uint32 mTicksCount;
};