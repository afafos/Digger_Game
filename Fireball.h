#pragma once

#include "GameObject.h"
#include "Map.h"

// Êכאסס פאוינבמכא
class Fireball :
	public GameObject
{
private:	
public:
	Fireball();
	Fireball(Map* map, std::vector<GameObject*>* objects, int x, int y, int dx, int dy);
	virtual std::string getSprite() const;
	virtual void Update(float dt);
};


