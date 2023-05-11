#include "Ball.h"
#include <cmath>

Ball::Ball(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("src/ball1.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 0; 
    y = 0;
    width = 24;
    height = 24;

    SetDirection(1, 1);
}

Ball::~Ball()
{
    SDL_DestroyTexture(texture);
}

void Ball::Update(float deltatime)
{
    x += _xdir * deltatime;
    y += _ydir * deltatime;
}

void Ball::Render(float deltatime)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(mRend, texture, nullptr, &rect);
}

void Ball::SetDirection(float xdir, float ydir)
{
    float length = sqrt(xdir * xdir + ydir * ydir);
    _xdir = BALL_SPEED * (xdir / length);
    _ydir = BALL_SPEED * (ydir / length);
}