#pragma once
#include "GameObject.h"
#include "Map.h"

// Класс врага
class Enemy :
    public GameObject
{
private:
	// Координаты ячейки, куда враг движется
	int nextx;
	int nexty;
	// Генерация следующего направления случайного
	void genNextDirection();
	// Проверка наличия непроходимых объектов по координатам
	bool isSolidObjectAt(int i, int j) const;
public:
	Enemy();
	Enemy(Map* map, std::vector<GameObject*>* objects, int x, int y);
	virtual bool isEnemy() const;
	virtual std::string getSprite() const;
	virtual void Update(float dt);	
};

