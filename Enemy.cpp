#include "Enemy.h"
#include <vector>

// �������� �����
const int SPEED = 2 * GameObject::SIZE;

// �������� ����������� �������� ������������ �������� - ����-�����, ����-�����
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
	// ��� �������� �������� - ������ �����
	int stepx[4]{ -1, 1, 0, 0 };
	int stepy[4]{ 0, 0, 1, -1 };
	
	// ���� ����������� �������� - �������� ������� ������, ����� � �������� ��������
	std::vector<int> dirs;
	for (int i = 0; i < 4; i++)
		if ((map->isFree(getCellI() + stepx[i], getCellJ() + stepy[i])) &&
			(!isSolidObjectAt(getCellI() + stepx[i], getCellJ() + stepy[i])) &&
			(!isRevers(dx, dy, stepx[i], stepy[i])))
			dirs.push_back(i);
	// ���� ��������� ���, �� ��� �������, ���� �����
	if (dirs.size() == 0) {
		dx = -dx;
		dy = -dy;
	}
	else {
		// ����� �������� ��������
		int dsel = rand() % dirs.size();
		dx = stepx[dirs[dsel]];
		dy = stepy[dirs[dsel]];
	}
	// �������� ��������� �� �����
	x = getCellI() * GameObject::SIZE;
	y = getCellJ() * GameObject::SIZE;
	// � ����������, ���� ������ ������
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
	// ���� ���� �����, �� ������ ����� ��������
	if ((dx == 0) && (dy == 0)) 
		genNextDirection();
	
	// ���� �� �������� ����� ���������� �� ��������� ��������, �� ������ ����� ��������
	if (((y - nexty) * (y + SPEED * dy * dt - nexty) <= 0) &&
		((x - nextx) * (x + SPEED * dx * dt - nextx) <= 0)) 
		genNextDirection();
		
	// ��������� ����������
	x += SPEED * dx * dt;
	y += SPEED * dy * dt;

	// ���� ����� ������, �� �������� ��� � �����
	for (int i = 0; i < objects->size(); i++)
		if (objects->at(i)->isIntersectWith(this)) {
			if (objects->at(i)->isGrabbable())
				objects->at(i)->Remove();
		}
}
