#include "Game.h"

const int thickness = 15;

Game::Game()
:mWindow(nullptr)
,mIsRunning(true)
,mHeight(768)
,mWidth(1024)
,mTicksCount(0)
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

    mPaddlePos.x = 10.0f;
	mPaddlePos.y = mHeight/2.0f;
    mPaddleVel = 500.0f;
    paddleH = 200;
	mBallPos.x = mWidth/2.0f;
	mBallPos.y = mHeight/2.0f;
    mBallVel.x = -200.0f;
    mBallVel.y = 100.0f;
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
        UpdateGame();
        GenerateOutput();
    }
}

void Game::UpdateGame() 
{

    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    mTicksCount = SDL_GetTicks();

    if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}

    if(mPaddleDir != 0)
    {
        mPaddlePos.y += mPaddleDir * mPaddleVel * deltaTime;
        float mPaddleUpper = paddleH/2.0f + thickness;
        float mPaddleLower = mHeight - paddleH/2.0f - thickness;

        if(mPaddlePos.y < (mPaddleUpper))
        {
            mPaddlePos.y = mPaddleUpper;
        }
        else if(mPaddlePos.y > mPaddleLower)
        {
            mPaddlePos.y = mPaddleLower;
        }
    }

    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;

    if(mBallPos.y <= thickness && mBallVel.y < 0.0f)
    {
        mBallVel.y *= -1;
    }
    if(mBallPos.y >= mHeight - thickness && mBallVel.y > 0.0f)
    {
        mBallVel.y *= -1;
    }
    if(mBallPos.x <= 0.0f && mBallVel.x < 0.0f)
    {
        mIsRunning = false;
    }
    if(mBallPos.x >= mWidth - thickness && mBallVel.x > 0.0f)
    {
        mBallVel.x *= -1;
    }

    float diff = abs(mPaddlePos.y - mBallPos.y);
    if (
        diff <= paddleH / 2.0f &&
        mBallPos.x <= mPaddlePos.x + thickness &&
        mBallVel.x < 0.0f
    )
    {
        mBallVel.x *= -1.0f;
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

    mPaddleDir = 0;
    if (state[SDL_SCANCODE_W])
    {
        mPaddleDir = -1;
    }
    if (state[SDL_SCANCODE_S])
    {
        mPaddleDir = 1;
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

    SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH/2),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);

    SDL_Rect ball {
        static_cast<int>(mBallPos.x - thickness / 2),
        static_cast<int>(mBallPos.y - thickness / 2),
        thickness,
        thickness
    };

    SDL_RenderFillRect(mRenderer, &ball);

    SDL_RenderPresent(mRenderer);
}