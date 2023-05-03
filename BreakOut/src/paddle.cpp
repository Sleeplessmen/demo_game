#include "paddle.h"
#include "math.h"

Paddle::Paddle(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("paddle.png");
    ptexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    width = 128;
    height = 32;
    
    // x
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
    rect.x = round(x);
    rect.y = round(y);
    rect.w = width;
    rect.h = height;
    SDL_RenderCopy(mRend, ptexture, 0, &rect);
}