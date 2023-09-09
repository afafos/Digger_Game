#pragma once

#include "GameObject.h"

// Класс мешка золота
class GoldBag :
    public GameObject
{
public:
    GoldBag();
    GoldBag(Map* map, std::vector<GameObject*>* objects, int x, int y);
    virtual std::string getSprite() const;
    virtual bool isSolid() const;
    virtual bool isMovable() const;
    virtual void Update(float dt);
};

