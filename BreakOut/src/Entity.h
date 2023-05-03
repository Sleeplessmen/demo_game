#ifndef entity_h_
#define entity_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Entity 
{
public:
    Entity(SDL_Renderer* renderer);
    virtual ~Entity();

    virtual void Update(float deltatime);
    virtual void Render(float deltatime);

    bool CollideCheck(Entity* other);
    float x, y, width, height;

protected:
    SDL_Renderer* mRend;
};


#endif /* ENTITY */