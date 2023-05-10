#include "paddle.h"
#include <cmath>

Paddle::Paddle(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("src/paddle.png");
    ptexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    width = 128;
    height = 32;

    y = 560;
}

Paddle::~Paddle()
{
    SDL_DestroyTexture(ptexture);
}

void Paddle::Update(float deltatime)
{

}

void Paddle::Render(float deltatime)
{
    SDL_Rect rect;
    rect.x = int(x + 0.5f);
    rect.y = int(y + 0.5f);
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(mRend, ptexture, nullptr, &rect);
}