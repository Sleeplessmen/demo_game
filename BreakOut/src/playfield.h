#ifndef board_h_
#define board_h_

#include "Entity.h"

#define PLAYFIELD_WIDTH 12
#define PLAYFIELD_HEIGHT 8
#define BRICK_WIDTH 64
#define BRICK_HEIGHT 24

class Brick 
{
public:
    int type;
    bool state;
};

class Playfield: public Entity
{
public:
    Playfield(SDL_Renderer* renderer);
    ~Playfield();

    void Update(float deltatime);
    void Render(float deltatime);
    void NewLevel();

    float brickoffsetx, brickoffsety;

    // define two-dimensional array of bricks
    Brick bricks[PLAYFIELD_WIDTH][PLAYFIELD_HEIGHT];

private:
    SDL_Texture* texture;
    
};

#endif /* Playfield */