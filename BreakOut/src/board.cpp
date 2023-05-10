#include "board.h"
#include <stdlib.h>
#include <time.h>

Board::Board(SDL_Renderer* renderer): Entity(renderer)
{
    SDL_Surface* surface = IMG_Load("src/bricks.png");
    bricktexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("src/side.png");
    sidetexture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    srand(time(0));

    x = 16;
    y = 0;
    width = 768;
    height = 600;

    brickoffsetx = 0;
    brickoffsety = 16;
}


Board::~Board()
{
    SDL_DestroyTexture(bricktexture);
    SDL_DestroyTexture(sidetexture);
}

void Board::Update(float deltatime)
{

}

void Board::Render(float deltatime)
{
    for(int i = 0; i < BOARD_WIDTH; i++) 
    {
        for(int j = 0; j < BOARD_HEIGHT; j++)
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

            SDL_RenderCopy(mRend, bricktexture, &srcrect, &dstrect);
        }
    }

    // Render sides
    SDL_Rect dstrect;
    dstrect.x = 0; 
    dstrect.y = 0;
    dstrect.w = 16;
    dstrect.h = 600;
    SDL_RenderCopy(mRend, sidetexture, 0, &dstrect);

    dstrect.x = 800 - 16; 
    dstrect.y = 0;
    dstrect.w = 16;
    dstrect.h = 600;
    SDL_RenderCopy(mRend, sidetexture, 0, &dstrect);
}

void Board::createLevel()
{
    for(int i = 0; i < BOARD_WIDTH; i++)
    {
        for(int j = 0; j < BOARD_HEIGHT; j++)
        {
            Brick brick;
            brick.type = rand() % 4; // 0 1 2 3 random color
            brick.state = true; // Brick is present
            bricks[i][j] = brick;
        }
    }
}


