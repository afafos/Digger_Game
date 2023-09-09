#pragma once
#include "GameObject.h"
#include "Map.h"

// Enemy class
class Enemy :
    public GameObject
{
private:
	// Coordinates of the cell where the enemy is moving
	int nextx;
	int nexty;
	// Generating the next random direction
	void genNextDirection();
	// Checking the presence of impassable objects by coordinates
	bool isSolidObjectAt(int i, int j) const;
public:
	Enemy();
	Enemy(Map* map, std::vector<GameObject*>* objects, int x, int y);
	virtual bool isEnemy() const;
	virtual std::string getSprite() const;
	virtual void Update(float dt);	
};

