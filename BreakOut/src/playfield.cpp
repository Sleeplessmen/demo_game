#include "playfield.h"
#include <stdlib.h>
#include <time.h>

Playfield::Playfield(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("src/bricks.png");
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    srand(time(0));

    x = 16;
    y = 0;
    width = 768;
    height = 600;

    brickoffsetx = 0;
    brickoffsety = 16;
}


Playfield::~Playfield()
{
    SDL_DestroyTexture(texture);
}

void Playfield::Update(float deltatime)
{

}

void Playfield::Render(float deltatime)
{
    // render bricks
    for(int i = 0; i < PLAYFIELD_WIDTH; i++) 
    {
        for(int j = 0; j < PLAYFIELD_HEIGHT; j++)
        {
            Brick brick = bricks[i][j];

            if(!brick.state) continue;
            SDL_Rect srcrect;
            srcrect.x = (brick.type%2) * BRICK_WIDTH;
            srcrect.y = (brick.type/2) * BRICK_HEIGHT;
            srcrect.w = BRICK_WIDTH;
            srcrect.h = BRICK_HEIGHT;

            SDL_Rect dstrect;
            dstrect.x = x + brickoffsetx + i*BRICK_WIDTH;
            dstrect.y = y + brickoffsety + j*BRICK_HEIGHT;
            dstrect.w = BRICK_WIDTH;
            dstrect.h = BRICK_HEIGHT;

            SDL_RenderCopy(mRend, texture, &srcrect, &dstrect);
        }
    }
}

void Playfield::NewLevel()
{
    for(int i = 0; i < PLAYFIELD_WIDTH; i++)
    {
        for(int j = 0; j < PLAYFIELD_HEIGHT; j++)
        {
            Brick brick;
            brick.type = rand() % 4; // 0 1 2 3 random color
            brick.state = true; // Brick is present
            bricks[i][j] = brick;
        }
    }
}


