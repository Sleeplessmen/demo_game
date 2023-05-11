#include "paddle.h"
#include <cmath>

Paddle::Paddle(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("src/paddle1.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    x = 0;
    y = 560;
    width = 128;
    height = 32;
}

Paddle::~Paddle()
{
    SDL_DestroyTexture(texture);
}

void Paddle::Update(float deltatime)
{

}

void Paddle::Render(float deltatime)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(mRend, texture, nullptr, &rect);
}