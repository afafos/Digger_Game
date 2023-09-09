#pragma once
#include "GameObject.h"
#include "Map.h"

// ����� �����
class Enemy :
    public GameObject
{
private:
	// ���������� ������, ���� ���� ��������
	int nextx;
	int nexty;
	// ��������� ���������� ����������� ����������
	void genNextDirection();
	// �������� ������� ������������ �������� �� �����������
	bool isSolidObjectAt(int i, int j) const;
public:
	Enemy();
	Enemy(Map* map, std::vector<GameObject*>* objects, int x, int y);
	virtual bool isEnemy() const;
	virtual std::string getSprite() const;
	virtual void Update(float dt);	
};

