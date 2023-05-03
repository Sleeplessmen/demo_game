#ifndef board_h_
#define board_h_

#include "Entity.h"

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 12
#define BRICK_WIDTH 64
#define BRICK_HEIGHT 24

class Brick 
{
public:
    int type;
    bool state;
};

class Board: public Entity
{
public:
    Board(SDL_Renderer* renderer);
    ~Board();

    void Update(float deltatime);
    void Render(float deltatime);
    void createLevel();

    float brickoffsetx, brickoffsety;

    // define two-dimensional array of bricks
    Brick bricks[BOARD_WIDTH][BOARD_HEIGHT];

private:
    SDL_Texture* bricktexture;
    SDL_Texture* sidetexture;
    
};

#endif /* BOARD */