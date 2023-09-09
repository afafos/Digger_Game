#pragma once
#include "GameObject.h"
#include "Map.h"
#include "Counter.h"

// Команды для игрока - движение и остановка
enum Command { cmdNone, cmdLeft, cmdRight, cmdUp, cmdDown, cmdStop };
// Направление игрока - сохраняется даже при остановке, указывая последнее движение
enum Direction { dirLeft, dirRight, dirUp, dirDown };

// Класс игрока
class Player :
    public GameObject
{
private:
	// Команда
	Command cmd;
	// Направление
	Direction lastdir;
	// Счетчик готовности выстрела
	Counter fireprepare;
public:
	Player();
	// Конструктор с картой и объектами
	Player(Map* map, std::vector<GameObject*>* objects, int x, int y);
	virtual std::string getSprite() const;
	virtual void Update(float dt);
	// Получение направления
	Direction getDirection() const;
	// Команды от игрока - движение, стоп и выстрел
	void sendLeft();
	void sendRight();
	void sendUp();
	void sendDown();
	void sendStop();
	void tryFire();
};

