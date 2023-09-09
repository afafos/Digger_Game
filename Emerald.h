#pragma once
#include "GameObject.h"

// Класс изумруда
class Emerald :
    public GameObject
{
public:
    Emerald();
    Emerald(Map* map, std::vector<GameObject*>* objects, int x, int y);
    virtual std::string getSprite() const;
    virtual bool isTreasure() const;
    virtual bool isGrabbable() const;
};

