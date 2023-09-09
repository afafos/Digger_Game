#pragma once
#include <string>
#include <vector>

// ����������� ���������� ��� ������ �� �������� ������
class Map;

// ������� ����� ��� ������� ��������
class GameObject
{
protected:
	// ���������
	float x;
	float y;
	// ����������� �������� (�� ��������! ����� ������ -1, 0 � 1)
	int dx;
	int dy;
	// ����� �������� �������
	bool isremoved;
	// ������ �� ����� - ������� ����� ����� ���������
	Map * map;
	// ������ �� ��� ������� - � ���� ���� ������������������
	std::vector<GameObject*> * objects;
public:
	// ����������� - �� ������� �� �����, ������� � ��������� �������
	GameObject(Map * map, std::vector<GameObject*> * objects, int x, int y);
	// ����������� �������
	GameObject();
	// ����������� ����� ��������� ���� ������� �������
	virtual std::string getSprite() const = 0;
	// ����� ���� ������, ����������� �������� ������� ��������, �� ������ ������� ��� ��������������� ���� � ������
	// �������� ������� ���������� ��� �����
	virtual bool isTreasure() const;
	// �������� ������
	virtual bool isEnemy() const;
	// �������� ������������ ��� ������ � ��������
	virtual bool isSolid() const;
	// ����� ���� ������ ��������� � �������
	virtual bool isGrabbable() const;
	// ����� ��������� �������
	virtual bool isMovable() const;
	// �������� ����� �������� �������
	bool isRemoved() const;
	// ����� ��������� ����� �������� �������
	void Remove();
	// ��������� � ��������� ���������
	int getX() const;
	int getY() const;
	void setX(float x);
	void setY(float y);
	// ��������� ������� ������ �� ����� ��� �������� ��������� ������� (���������)
	int getCellI() const;
	int getCellJ() const;
	// ���������� �������
	virtual void Update(float dt);
	// �������� ����������� � ������ ��������
	bool isIntersectWith(const GameObject * obj) const;
	const static int SIZE = 50; // ������������� ������ �������� ��������
};

