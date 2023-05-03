#include "Ball.h"
#include "math.h"

Ball::Ball(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("ball.png");
    balltexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 0; 
    y = 0;
    width = 24;
    height = 24;

    SetDirection(-1, -1);
}

Ball::~Ball()
{
    SDL_DestroyTexture(balltexture);
}

void Ball::Update(float deltatime)
{
    x += _xdir * deltatime;
    y += _ydir * deltatime;
}

void Ball::Render(float deltatime)
{
    SDL_Rect rect;
    rect.x = round(x);
    rect.y = round(y);
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(mRend, balltexture, 0, &rect);
}

void Ball::SetDirection(float xdir, float ydir)
{
    float nor = sqrt(xdir * xdir + ydir * ydir);
    _xdir = BALL_SPEED * (xdir / nor);
    _ydir = BALL_SPEED * (ydir / nor);
}