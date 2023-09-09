#include "Emerald.h"

Emerald::Emerald():GameObject()
{
}

Emerald::Emerald(Map* map, std::vector<GameObject*>* objects, int x, int y):GameObject(map, objects, x,y)
{
}

bool Emerald::isTreasure() const
{
	return true;
}

bool Emerald::isGrabbable() const
{
	return true;
}

std::string Emerald::getSprite() const
{
	return "emerald";
}
