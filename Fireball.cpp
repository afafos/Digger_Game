#include "Fireball.h"

const int SPEED = 6 * GameObject::SIZE;

Fireball::Fireball() :GameObject()
{

}

Fireball::Fireball(Map* map, std::vector<GameObject*>* objects, int x, int y, int dx, int dy) : GameObject(map, objects, x, y)
{
	this->dx = dx;
	this->dy = dy;
}

std::string Fireball::getSprite() const
{
	return "fireball";
}

void Fireball::Update(float dt)
{	
	// Обновляем координаты
	x += SPEED * dx * dt;
	y += SPEED * dy * dt;

	// Если уперлись в стену, убираем себя
	if (!map->isFree(getCellI(), getCellJ())) Remove();
		
	for (int i = 0; i < objects->size(); i++)
		if (objects->at(i)->isIntersectWith(this)) {
			// Удаляем себя в любом случае при ударе об объект
			Remove();
			// Если объект враг, то и его тоже
			if (objects->at(i)->isEnemy()) objects->at(i)->Remove();			
		}
}
