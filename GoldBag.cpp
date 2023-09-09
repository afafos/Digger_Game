#include "GoldBag.h"
#include "Map.h"
#include "Gold.h"

const int SPEED = 4 * GameObject::SIZE;

GoldBag::GoldBag() :GameObject()
{
}

GoldBag::GoldBag(Map* map, std::vector<GameObject*>* objects, int x, int y) : GameObject(map, objects, x, y)
{
}

std::string GoldBag::getSprite() const
{
	return "goldbag";
}

bool GoldBag::isSolid() const
{
	return true;
}

bool GoldBag::isMovable() const
{
	return true;
}

void GoldBag::Update(float dt)
{	
	// Checking if the bag can fall
	bool canfall = true;
	// No, if downstairs is busy
	if (!map->isFree(getCellI(), getCellJ() + 1)) canfall = false;

	// No, if there are objects below
	for (int i = 0; i < objects->size(); i++)
		if ((objects->at(i)->getCellI() == getCellI()) && (objects->at(i)->getCellJ() == getCellJ()+1))
			canfall = false;

	if (canfall) {
		// If we fall, then we align by x
		x = getCellI() * GameObject::SIZE;
		// Move along y
		y += SPEED * dt;
		// If the bottom is busy
		if (!map->isFree(getCellI(), getCellJ() + 1)) {
			// Removing the object and creating gold
			Remove();
			Gold* g = new Gold(map, objects, getCellI() * GameObject::SIZE, getCellJ() * GameObject::SIZE);
			objects->push_back(g);
		}
		// If someone was crushed during the fall, then we remove him from the map
		for (int i = 0; i < objects->size(); i++)
			if ((objects->at(i)->getCellI() == getCellI()) && (objects->at(i)->getCellJ() == getCellJ() + 1))
				objects->at(i)->Remove();
	}
}
