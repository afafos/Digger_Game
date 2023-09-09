#include "Enemy.h"
#include <vector>

// Скорость врага
const int SPEED = 2 * GameObject::SIZE;

// Проверка инверсности скорости относительно заданной - лево-право, вниз-вверх
bool isRevers(int dx1, int dy1, int dx2, int dy2) {
	if ((dy1 == 0) && (dy2 == 0)) return dx1 == -dx2;
	if ((dx1 == 0) && (dx2 == 0)) return dy1 == -dy2;
	return false;
}

bool Enemy::isSolidObjectAt(int celli, int cellj) const {
	for (int i = 0; i < objects->size(); i++)
		if (objects->at(i)->isSolid())
			if ((objects->at(i)->getCellI() == celli) && (objects->at(i)->getCellJ() == cellj))
				return true;
	return false;
}

void Enemy::genNextDirection()
{	
	// Все варианты движений - четыре штуки
	int stepx[4]{ -1, 1, 0, 0 };
	int stepy[4]{ 0, 0, 1, -1 };
	
	// Тест возможности движения - исключая занятые ячейки, мешки и обратное движение
	std::vector<int> dirs;
	for (int i = 0; i < 4; i++)
		if ((map->isFree(getCellI() + stepx[i], getCellJ() + stepy[i])) &&
			(!isSolidObjectAt(getCellI() + stepx[i], getCellJ() + stepy[i])) &&
			(!isRevers(dx, dy, stepx[i], stepy[i])))
			dirs.push_back(i);
	// Если вариантов нет, то как минимум, идет назад
	if (dirs.size() == 0) {
		dx = -dx;
		dy = -dy;
	}
	else {
		// Иначе случайно выбираем
		int dsel = rand() % dirs.size();
		dx = stepx[dirs[dsel]];
		dy = stepy[dirs[dsel]];
	}
	// Фиксация координат по сетке
	x = getCellI() * GameObject::SIZE;
	y = getCellJ() * GameObject::SIZE;
	// И запоминаем, куда должны прийти
	nextx = x + dx * GameObject::SIZE;
	nexty = y + dy * GameObject::SIZE;	
}

Enemy::Enemy() :GameObject()
{	
}

Enemy::Enemy(Map* map, std::vector<GameObject*>* objects, int x, int y) : GameObject(map, objects, x, y)
{
}

bool Enemy::isEnemy() const
{
	return true;
}

std::string Enemy::getSprite() const
{
	return "enemy";
}

void Enemy::Update(float dt)
{	
	// Если враг стоит, то делаем новое движение
	if ((dx == 0) && (dy == 0)) 
		genNextDirection();
	
	// Если мы достигли точки назначения на следующей итерации, то делаем новое движение
	if (((y - nexty) * (y + SPEED * dy * dt - nexty) <= 0) &&
		((x - nextx) * (x + SPEED * dx * dt - nextx) <= 0)) 
		genNextDirection();
		
	// Обновляем координаты
	x += SPEED * dx * dt;
	y += SPEED * dy * dt;

	// Если нашли золото, то забираем его с карты
	for (int i = 0; i < objects->size(); i++)
		if (objects->at(i)->isIntersectWith(this)) {
			if (objects->at(i)->isGrabbable())
				objects->at(i)->Remove();
		}
}
