#pragma once
#include "GameObject.h"
#include "Map.h"
#include "Counter.h"

// ������� ��� ������ - �������� � ���������
enum Command { cmdNone, cmdLeft, cmdRight, cmdUp, cmdDown, cmdStop };
// ����������� ������ - ����������� ���� ��� ���������, �������� ��������� ��������
enum Direction { dirLeft, dirRight, dirUp, dirDown };

// ����� ������
class Player :
    public GameObject
{
private:
	// �������
	Command cmd;
	// �����������
	Direction lastdir;
	// ������� ���������� ��������
	Counter fireprepare;
public:
	Player();
	// ����������� � ������ � ���������
	Player(Map* map, std::vector<GameObject*>* objects, int x, int y);
	virtual std::string getSprite() const;
	virtual void Update(float dt);
	// ��������� �����������
	Direction getDirection() const;
	// ������� �� ������ - ��������, ���� � �������
	void sendLeft();
	void sendRight();
	void sendUp();
	void sendDown();
	void sendStop();
	void tryFire();
};

