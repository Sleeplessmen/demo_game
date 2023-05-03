#include "Entity.h"

Entity::Entity(SDL_Renderer* renderer)
{
    mRend = renderer;
    x = 0; 
    y = 0;
    width = 1;
    height = 1;
}

Entity::~Entity()
{

}

void Entity::Update(float deltatime)
{

}

void Entity::Render(float deltatime)
{

}

bool Entity::CollideCheck(Entity* other)
{
    if(x + width > other->x && x < other->width + other->x &&
    y + height > other->y && y < other->height + other->y)
    {
        return true;
    }
    return false;
}