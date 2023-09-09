#include "GameObject.h"

GameObject::GameObject(Map* map, std::vector<GameObject*> * objects, int x, int y)
{
    isremoved = false;
    this->x = x;
    this->y = y;
    this->map = map;
    this->objects = objects;
    dx = 0;
    dy = 0;
}

GameObject::GameObject()
{
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
    isremoved = false;
}

bool GameObject::isTreasure() const 
{
    return false;
}

bool GameObject::isEnemy() const
{
    return false;
}

bool GameObject::isSolid() const
{
    return false;
}

bool GameObject::isGrabbable() const
{
    return false;
}

bool GameObject::isMovable() const
{
    return false;
}

bool GameObject::isRemoved() const
{
    return isremoved;
}

void GameObject::Remove()
{
    isremoved = true;
}

int GameObject::getX() const
{
    return (int)x;
}

int GameObject::getY() const
{
    return (int)y;
}

void GameObject::setX(float x)
{
    this->x = x;
}

void GameObject::setY(float y)
{
    this->y = y;
}

// «десь вычисление €чейки объекта на карте, ближайша€ к объекту
int GameObject::getCellI() const
{
    return round((float)x / (float)SIZE);
}

int GameObject::getCellJ() const
{
    return round((float)y / (float)SIZE);
}

void GameObject::Update(float dt)
{    
}

bool GameObject::isIntersectWith(const GameObject * obj) const
{
    return (getCellI() == obj->getCellI()) && (getCellJ() == obj->getCellJ());
}
