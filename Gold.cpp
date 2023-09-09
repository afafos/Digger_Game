#include "Gold.h"

Gold::Gold() :GameObject()
{
}

Gold::Gold(Map* map, std::vector<GameObject*>* objects, int x, int y) : GameObject(map, objects, x, y)
{
}

bool Gold::isGrabbable() const
{
	return true;
}

std::string Gold::getSprite() const
{
	return "gold";
}