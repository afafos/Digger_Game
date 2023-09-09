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
	// ���������, ����� �� ����� ������
	bool canfall = true;
	// ���, ���� ����� ������
	if (!map->isFree(getCellI(), getCellJ() + 1)) canfall = false;

	// ���, ���� ����� ���� �������
	for (int i = 0; i < objects->size(); i++)
		if ((objects->at(i)->getCellI() == getCellI()) && (objects->at(i)->getCellJ() == getCellJ()+1))
			canfall = false;

	if (canfall) {
		// ���� ������, �� ����������� �� x
		x = getCellI() * GameObject::SIZE;
		// ������� �� y
		y += SPEED * dt;
		// ���� ����� ������
		if (!map->isFree(getCellI(), getCellJ() + 1)) {
			// ������� ������ � ������� ������
			Remove();
			Gold* g = new Gold(map, objects, getCellI() * GameObject::SIZE, getCellJ() * GameObject::SIZE);
			objects->push_back(g);
		}
		// ���� � �������� ������� ����-�� ���������, �� ������� ��� � �����
		for (int i = 0; i < objects->size(); i++)
			if ((objects->at(i)->getCellI() == getCellI()) && (objects->at(i)->getCellJ() == getCellJ() + 1))
				objects->at(i)->Remove();
	}
}
