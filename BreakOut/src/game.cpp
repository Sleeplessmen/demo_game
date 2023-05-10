#include "game.h"
#include <iostream> 
#include <math.h>

Game::Game()
{
    mWin = 0;
    mRend = 0;
}

Game::~Game()
{

}

bool Game::Init()
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        std::cout << "Error init: " << SDL_GetError() << std::endl;
        return false;
    }

    // create window
    mWin = SDL_CreateWindow("BREAK OUT",
     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
    if(!mWin)
    {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    // create renderer
    mRend = SDL_CreateRenderer(mWin, -1, SDL_RENDERER_ACCELERATED);
    if(!mRend)
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    // initilize resources
    SDL_Surface* surface = IMG_Load("test.png");
    mText = SDL_CreateTextureFromSurface(mRend, surface);
    SDL_FreeSurface(surface);

    // initilize timing
    lasttick = SDL_GetTicks();
    fpstick = lasttick;
    fps = 0;
    framecount = 0;

    testx = 0;
    testy = 0;

    return true;
}


void Game::Run()
{
    mBoard = new Board(mRend);
    mPad = new Paddle(mRend);
    mBall = new Ball(mRend);

    NewGame();

    // Main loop
    while (true) {
        // Handler events
        SDL_Event e;
        if (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) 
            {
                break;
            }
        }

        // Calculate delta and fps
        unsigned int curtick = SDL_GetTicks();
        float dt = (curtick - lasttick) / 1000.0f;
        if (curtick - fpstick >= FPS_DELAY) {
            fps = framecount * (1000.0f / (curtick - fpstick));
            fpstick = curtick;
            framecount = 0;
            char buf[100];
            snprintf(buf, 100, "Breakout_remake(fps: %u)", fps);
            SDL_SetWindowTitle(mWin, buf);
        }
        else 
        {
            framecount++;
        }
        
        lasttick = curtick;

        // Update and render the game
        Update(dt);
        Render(dt);
    }

    delete mBoard;
    delete mPad;
    delete mBall;

    Clean();

    SDL_Quit();
}

void Game::Clean()
{
    SDL_DestroyTexture(mText);
    SDL_DestroyRenderer(mRend);
    SDL_DestroyWindow(mWin);
}

void Game::Update(float deltatime)
{
    // Input
    int mx, my;
    Uint8 mstate = SDL_GetMouseState(&mx, &my);
    SetPaddle(mx - mPad->width/2.0f);

    if(mstate&SDL_BUTTON(1))
    {
        if(paddlestick)
        {
            paddlestick = false;
            mBall->SetDirection(1, -1);
        }
    }

    if(paddlestick)
    {
        StickBall();
    }

    ball_boardCollisions();
    ball_paddleCollisions();
    ball_brickCollisions();

    if(!GetBrickCount()) 
    {
        NewGame();
    }

    mBoard->Update(deltatime);
    mPad->Update(deltatime);
    mBall->Update(deltatime);
}


void Game::Render(float deltatime)
{
    SDL_SetRenderDrawColor(mRend, 0, 0, 0, 255);
    SDL_RenderClear(mRend);

    mBoard->Render(deltatime);
    mPad->Render(deltatime);
    mBall->Render(deltatime);

    SDL_RenderPresent(mRend);
}

void Game::NewGame()
{
    mBoard->createLevel();
    ResetPaddle();
}
void Game::ResetPaddle()
{  
    paddlestick = true;
    StickBall();
}
void Game::StickBall() 
{
    mBall->x = mPad->x + mPad->width/2 - mBall->width/2;
    mBall->y = mPad->y - mBall->height;
}

void Game::SetPaddle(float x)
{
    float newx;
    if(x < mBoard->x)
    {
        newx = mBoard->x;   
    }
    else if (x + mPad->width > mBoard->x + mBoard->width)
    {
        newx = mBoard->x + mBoard->width;
    }
    
    mPad->x = newx;
}


void Game::ball_boardCollisions()
{
    // top and bottom
    if(mBall->y > mBoard->y)
    {
        mBall->y = mBoard->y;
        // reflect
        mBall->_ydir *= -1;
    } 
    else if(mBall->y + mBall->height > mBoard->y + mBoard->height)
    {
        // ball lost
        ResetPaddle();
    }

    // left and right
    if(mBall->x <= mBoard->x)
    {
        mBall->x = mBoard->x;
        mBall->_xdir *= -1;
    }
    else if(mBall->x + mBall->width >= mBoard->x + mBoard->width)
    {
        mBall->x = mBoard->x + mBoard->width - mBall->width;
        mBall->_xdir *= -1;
    }
}


float Game::paddle_ballReflection(float hitpoint_x)
{
    if(hitpoint_x < 0)
    {
        hitpoint_x = 0;
    }
    else if(hitpoint_x > mPad->width)
    {
        hitpoint_x = mPad->width;
    }
    
    
    hitpoint_x -= mPad->width/2.0f;
    // scale the reflection
    return 2.0f * (hitpoint_x / (mPad->width/2.0f));
}

void Game::ball_paddleCollisions()
{
    float ballcenter_x = mBall->x + mBall->width/2.0f;

    if(mBall->CollideCheck(mPad))
    {
        mBall->y = mPad->y - mBall->height;
        mBall->SetDirection(paddle_ballReflection(ballcenter_x - mPad->x), -1);
    }
}

void Game::ball_brickCollisions()
{
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        for(int j = 0; j < BOARD_HEIGHT; j++)
        {
            Brick brick = mBoard->bricks[i][j];

            if(brick.state)
            {
                float ballcenter_x = mBall->x + mBall->width/2.0f;
                float ballcenter_y = mBall->y + mBall->height/2.0f;

                float brick_x = mBoard->x + mBoard->brickoffsetx + i*BRICK_WIDTH;
                float brick_y = mBoard->y + mBoard->brickoffsety + j*BRICK_HEIGHT;

                float brickcenter_x = brick_x + BRICK_WIDTH/2.0f;
                float brickcenter_y = brick_y + BRICK_HEIGHT/2.0f;

                if(mBall->x < brick_x + BRICK_WIDTH && mBall->x + mBall->width > brick_x &&
                mBall->y < brick_y + BRICK_HEIGHT && mBall->y + mBall->height > brick_y)
                {
                    // Collision detected, remove the brick 
                    mBoard->bricks[i][j].state = false;
                    float ymin = (brick_y > mBall->y) ? brick_y : mBall->y;
                    float ymax = (brick_y + BRICK_HEIGHT < mBall->y + mBall->height) ? brick_y + BRICK_HEIGHT : mBall->y + mBall->height;
                    float dy = ymax - ymin;

                    float xmin = (brick_x > mBall->x) ? brick_x : mBall->x;
                    float xmax = (brick_x + BRICK_WIDTH < mBall->x + mBall->width) ? brick_x + BRICK_WIDTH : mBall->x + mBall->width;
                    float dx = xmax - xmin;

                    if(dx > dy)
                    {
                        if(ballcenter_y > brickcenter_y)
                        {
                            // Bottom
                            mBall->y += dy + 0.01f;
                            ball_brickResponse(3);   
                        }
                        else 
                        {
                            // Top
                            mBall->y -= dy + 0.01f;
                            ball_brickResponse(1);
                        }
                    }
                    else
                    {
                        if(ballcenter_x < brickcenter_x)
                        {
                            // Left 
                            mBall->x -= dx + 0.01f;
                            ball_brickResponse(0);
                        }
                        else 
                        {
                            // Right 
                            mBall->x += dx + 0.01f;
                            ball_brickResponse(2);
                        }
                    }

                    return;
                }
            }

        }
    }
}


void Game::ball_brickResponse(int dirindex)
{
    //dirindex 
    // 0-left 1-top 2-right 3-bottom

    // direction factors
    int mulx = 1;
    int muly = 1;

    if(mBall->_xdir > 0) // positive x direction
    {
        if(mBall->_ydir > 0) // positive y direction
        {
            if(dirindex == 0 || dirindex == 3)
            {
                mulx = -1;
            }
            else muly = -1;
        }

        else if(mBall->_ydir < 0) // negative y direction
        {
            if(dirindex == 0 || dirindex == 1)
            {
                mulx = -1;
            }
            else muly = -1;
        }
    }
    
    else if(mBall->_xdir < 0) // negative x direction 
    {
        if(mBall->_ydir > 0)
        {
            if(dirindex == 2 || dirindex == 3)
            {
                mulx = -1;
            }
            else muly = -1;
        }

        else if(mBall->_ydir < 0)
        {
            if(dirindex == 1 || dirindex == 2)
            {
                mulx = -1;
            }
            else muly = -1;
        }
    }

    mBall->SetDirection(mulx * mBall->_xdir, muly * mBall->_ydir);
}

int Game::GetBrickCount()
{
    int brickcount = 0;
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        for(int j = 0; j < BOARD_HEIGHT; j++)
        {
            if(mBoard->bricks[i][j].state) brickcount++;
        }
    }
    return brickcount;
}
