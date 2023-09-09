#include "Player.h"
#include "Fireball.h"

// �������� ������ � ���������
const int SPEED = 2 * GameObject::SIZE;
const int FIREBALL_INTERVAL = 10;

// ������� ����������� � -1/0/-1
int dxbydir(Direction dir) {
	if (dir == dirLeft) return -1;
	if (dir == dirRight) return 1;
	return 0;
}

int dybydir(Direction dir) {
	if (dir == dirUp) return -1;
	if (dir == dirDown) return 1;
	return 0;
}

Player::Player() :GameObject()
{
	cmd = cmdNone;
	lastdir = dirRight;
	// ���������� �������� �� ��������� ����� ��� �������� ������
	fireprepare.upset(0);
}

Player::Player(Map* map, std::vector<GameObject*>* objects, int x, int y) : GameObject(map, objects, x, y)
{	
	cmd = cmdNone;
	lastdir = dirRight;
}

std::string Player::getSprite() const
{
	return "digger";
}

void Player::Update(float dt)
{
	// ����� ������ ����������� ��������, � ����������� �� �������� �������� � ��������� �������
	int nearj = y / SIZE;
	if (dy > 0) nearj++;
	int neari = x / SIZE;
	if (dx > 0) neari++;

	switch (cmd)
	{
	case cmdLeft:
		// ��� ������� �����, ������� ������ �� ������� ������, ��������������� �����
		if ((y - nearj * SIZE) * (y + SPEED * dy * dt - nearj * SIZE) <= 0) {
			y = nearj * SIZE;
			dx = -1;
			dy = 0;
			lastdir = dirLeft;
			cmd = cmdNone;
		}
		break;
		// ��������� ����������
	case cmdRight:
		if ((y - nearj * SIZE) * (y + SPEED * dy * dt - nearj * SIZE) <= 0) {
			y = nearj * SIZE;
			dx = 1;
			dy = 0;
			lastdir = dirRight;
			cmd = cmdNone;
		}
		break;
	case cmdUp:
		if ((x - neari * SIZE) * (x + SPEED * dx * dt - neari * SIZE) <= 0) {
			x = neari * SIZE;
			dx = 0;
			dy = -1;
			lastdir = dirDown;
			cmd = cmdNone;
		}
		break;
	case cmdDown:
		if ((x - neari * SIZE) * (x + SPEED * dx * dt - neari * SIZE) <= 0) {
			x = neari * SIZE;
			dx = 0;
			dy = 1;
			lastdir = dirUp;
			cmd = cmdNone;
		}
		break;
	case cmdStop:
		// ������� ��������� ��������, ��� ������ ����������� ����� ���������� ������� �����
		if (dy != 0)
			if ((y - nearj * SIZE) * (y + SPEED * dy * dt - nearj * SIZE) <= 0) {
				y = nearj * SIZE;
				dx = 0;
				dy = 0;
				cmd = cmdNone;
			}
		if (dx != 0)
			if ((x - neari * SIZE) * (x + SPEED * dx * dt - neari * SIZE) <= 0) {
				x = neari * SIZE;
				dx = 0;
				dy = 0;
				cmd = cmdNone;
			}
		break;
	default:
		break;
	}

	// ���������� ���������
	x += SPEED * dx * dt;
	y += SPEED * dy * dt;

	// ���������� �������� ��������
	fireprepare.update(dt);

	// ����, ���� ����� �� ������� �����
	if ((dx < 0) && (x < 0)) {
		x = 0;
		dx = 0;
	}
	if ((dy < 0) && (y < 0)) {
		y = 0;
		dy = 0;
	}
	if ((dx > 0) && (x > (map->getWidth() - 1) * SIZE)) {
		x = (map->getWidth() - 1) * SIZE;
		dx = 0;
	}
	if ((dy > 0) && (y > (map->getHeight() - 1) * SIZE)) {
		y = (map->getHeight() - 1) * SIZE;
		dy = 0;
	}

	// ������ �������� ������ � ������� �� ��������
	for (int i = 0; i < objects->size(); i++)
		if (objects->at(i)->isMovable()) {
			// ��� ��������� - ������ ��������
			if (dy > 0) {
				int sy = y + GameObject::SIZE - objects->at(i)->getCellJ() * GameObject::SIZE;
				if ((sy > 0) && (sy < GameObject::SIZE) && (getCellI() == objects->at(i)->getCellI())) {
					y = (objects->at(i)->getCellJ() - 1) * GameObject::SIZE;
					dy = 0;
				}
			}
			if (dy < 0) {
				int sy = objects->at(i)->getCellJ() * GameObject::SIZE + GameObject::SIZE - y ;
				if ((sy > 0) && (sy < GameObject::SIZE) && (getCellI() == objects->at(i)->getCellI())) {
					y = (objects->at(i)->getCellJ() + 1) * GameObject::SIZE;
					dy = 0;
				}
			}
			// ��� ����������� - ������� �����, ���� ������ �� ��� ��������
			if (dx > 0) {
				int sx = x + GameObject::SIZE - objects->at(i)->getX();
				if ((sx > 0) && (sx < GameObject::SIZE) && (getCellJ() == objects->at(i)->getCellJ())) {
					if (map->isFree((int)(x/GameObject::SIZE + 2),getCellJ()))
						objects->at(i)->setX(x+GameObject::SIZE);
					else {
						x = getCellI() * GameObject::SIZE;
						dx = 0;
					}
				}
			}
			if (dx < 0) {
				int sx = objects->at(i)->getX() + GameObject::SIZE - x;
				if ((sx > 0) && (sx < GameObject::SIZE) && (getCellJ() == objects->at(i)->getCellJ())) {
					if (map->isFree((int)(x / GameObject::SIZE) - 1, getCellJ()))
						objects->at(i)->setX(x - GameObject::SIZE);
					else {
						x = getCellI() * GameObject::SIZE;
						dx = 0;
					}
				}
			}
		}

	// ������� �����, ��� ������ ������
	map->clearCell(getCellI(),getCellJ());

	// ������ �������� - ��������� � ������
	for (int i=0; i<objects->size(); i++)
		if (objects->at(i)->isIntersectWith(this)) {
			// ������ ��������, ������� �����
			if (objects->at(i)->isGrabbable()) objects->at(i)->Remove();
			// ������� � ������ - �������� ����
			if (objects->at(i)->isEnemy()) Remove();
		}
}

Direction Player::getDirection() const
{
	return lastdir;
}

void Player::sendLeft()
{
	// ������� ����� - ���� �����, �� ����� ������, ����� ��������� � ���������� �����
	if (dy == 0) {
		dx = -1;
		lastdir = dirLeft;
	}
	else cmd = cmdLeft;
}

void Player::sendRight()
{
	if (dy == 0) {
		dx = 1;
		lastdir = dirRight;
	}
	else cmd = cmdRight;
}

void Player::sendUp()
{
	if (dx == 0) {
		dy = -1;
		lastdir = dirUp;
	}
	else cmd = cmdUp;
}

void Player::sendDown()
{
	if (dx == 0) {
		dy = 1;
		lastdir = dirDown;
	}
	else cmd = cmdDown;
}

void Player::sendStop()
{
	cmd = cmdStop;
}

// ������� ��������, ���� ������� �����
void Player::tryFire()
{
	if (!fireprepare.isActive()) {
		// ��������� �������� � ����������� ���������� ��������
		Fireball* f = new Fireball(map, objects, x, y, dxbydir(lastdir), dybydir(lastdir));
		objects->push_back(f);
		fireprepare.upset(FIREBALL_INTERVAL);
	}
}
