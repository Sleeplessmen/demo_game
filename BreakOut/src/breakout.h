#ifndef game_h_
#define game_h_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "ball.h"
#include "playfield.h"
#include "paddle.h"

#define FPS_DELAY 500
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

class Game
{
public:
    Game();
    ~Game();

    bool Init();
    void Run();

private:
    SDL_Window* mWin;
    SDL_Renderer* mRend;
    SDL_Texture* mText;

    // Timing
    unsigned int lasttick, fpstick, fps, framecount;

    // Objects
    Playfield* mPlayfield;
    Paddle* mPad;
    Ball* mBall;

    // Flags
    bool ballStickToPaddle;

    void Clean();
    void Update(float deltatime);
    void Render(float deltatime);

    void NewGame();
    void ResetPaddle();
    void StickBallToPaddle();

    void SetPaddle(float x);

    void ball_playfieldCollisions();
    void ball_paddleCollisions();
    float paddle_ballReflection(float hitpointx);
    void ball_brickCollisions();
    void ball_brickReflection(int dirindex);
    int GetBrickCount();
};

#endif 