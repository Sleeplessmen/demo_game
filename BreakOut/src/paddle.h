#ifndef paddle_h_
#define paddle_h_

#include "Entity.h"

class Paddle : public Entity
{
public:
    Paddle(SDL_Renderer* renderer);
    ~Paddle();

    void Update(float deltatime);
    void Render(float deltatime);

private:
    SDL_Texture* ptexture;
};

#endif