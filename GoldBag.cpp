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
	// Проверяем, может ли мешок падать
	bool canfall = true;
	// Нет, если снизу занято
	if (!map->isFree(getCellI(), getCellJ() + 1)) canfall = false;

	// Нет, если снизу есть объекты
	for (int i = 0; i < objects->size(); i++)
		if ((objects->at(i)->getCellI() == getCellI()) && (objects->at(i)->getCellJ() == getCellJ()+1))
			canfall = false;

	if (canfall) {
		// Если падаем, то выравниваем по x
		x = getCellI() * GameObject::SIZE;
		// двигаем по y
		y += SPEED * dt;
		// Если снизу занято
		if (!map->isFree(getCellI(), getCellJ() + 1)) {
			// Удаляем объект и создаем золото
			Remove();
			Gold* g = new Gold(map, objects, getCellI() * GameObject::SIZE, getCellJ() * GameObject::SIZE);
			objects->push_back(g);
		}
		// Если в процессе падения кого-то придавили, то убираем его с карты
		for (int i = 0; i < objects->size(); i++)
			if ((objects->at(i)->getCellI() == getCellI()) && (objects->at(i)->getCellJ() == getCellJ() + 1))
				objects->at(i)->Remove();
	}
}
