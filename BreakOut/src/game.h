#ifndef game_h_
#define game_h_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Ball.h"
#include "board.h"
#include "paddle.h"

#define FPS_DELAY 500

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

    // Test
    float testx, testy;

    Board* mBoard;
    Paddle* mPad;
    Ball* mBall;
    bool paddlestick;

    void Clean();
    void Update(float deltatime);
    void Render(float deltatime);

    void NewGame();
    void Reset();
    void ResetBall();

    void SetPaddle(float x);

    void ball_boardCollisions();

    void ball_paddleCollisions();
    float paddle_ballReflection(float hitpointx);

    void ball_brickCollisions();
    void ball_brickResponse(int dirindex);
    int GetBrickCount();
};

#endif 