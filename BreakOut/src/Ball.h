#ifndef ball_h_
#define ball_h_

#include "Entity.h"

const float BALL_SPEED = 500;

class Ball : public Entity
{
public:
    Ball(SDL_Renderer* renderer);
    ~Ball();

    void Update(float deltatime);
    void Render(float deltatime);

    void SetDirection(float xdir, float ydir);

    float _xdir, _ydir;
private:
    SDL_Texture* balltexture;
};

#endif 