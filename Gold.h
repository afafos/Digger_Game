#pragma once
#include "GameObject.h"

// Gold pile class
class Gold :
    public GameObject
{
public:
    Gold();
    Gold(Map* map, std::vector<GameObject*>* objects, int x, int y);
    virtual std::string getSprite() const;
    virtual bool isGrabbable() const; 
};
