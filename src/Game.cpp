#include "Game.h"

const int thickness = 15;

Game::Game()
:mWindow(nullptr)
,mIsRunning(true)
,mHeight(768)
,mWidth(1024)
{
	
}

bool Game::Initialize()
{
    //SDL_INIT_VIDEO is set for creating a window
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    // sdlResult == 0 indicates initialization succeed; otherwise there is something failed.
    if(sdlResult !=  0)
    {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
        "title",
        100,
        100,
        mWidth,
        mHeight,
        0 // Flags (0 for no flags set)
    );

    if(!mWindow)
    {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(
        mWindow,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if(!mRenderer)
    {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    return true;
}


void Game::Shutdown()
{
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRenderer);
    SDL_Quit();
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInput();
        GenerateOutput();
    }
}

void Game::ProcessInput() 
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
        }
    }

    const Uint8* state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::GenerateOutput()
{
    SDL_SetRenderDrawColor(
		mRenderer,
		0,		// R
		0,		// G 
		255,	// B
		255		// A
	);

    SDL_RenderClear(mRenderer);

    SDL_SetRenderDrawColor(
        mRenderer,
        255,      //R
        255,      //G
        255,      //B
        255       //A
    );

	SDL_Rect wall{
		0,			// Top left x
		0,			// Top left y
		mWidth,		// Width
		thickness	// Height
	};
	SDL_RenderFillRect(mRenderer, &wall);

    wall.y = mHeight - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	wall.x = mWidth - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = mHeight;
	SDL_RenderFillRect(mRenderer, &wall);

    SDL_RenderPresent(mRenderer);
}