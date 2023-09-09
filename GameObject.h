#pragma once
#include <string>
#include <vector>

// Опережающая декларация для защиты от круговых ссылок
class Map;

// Базовый класс для игровых объектов
class GameObject
{
protected:
	// Положение
	float x;
	float y;
	// Направление скорости (не скорость! здесь только -1, 0 и 1)
	int dx;
	int dy;
	// Метка удаления объекта
	bool isremoved;
	// Ссылка на карту - объекту нужно знать окружение
	Map * map;
	// Ссылка на все объекты - с ними надо взаимодейстсвовать
	std::vector<GameObject*> * objects;
public:
	// Конструктор - со ссылкой на карту, объекты и начальную позицию
	GameObject(Map * map, std::vector<GameObject*> * objects, int x, int y);
	// Конструктор базовый
	GameObject();
	// Виртуальный метод получения кода спрайта объекта
	virtual std::string getSprite() const = 0;
	// Далее идут методы, описывающие свойства игровых объектов, на основе которых они взаимодействуют друг с другом
	// Является целевым сокровищем для сбора
	virtual bool isTreasure() const;
	// Является врагом
	virtual bool isEnemy() const;
	// Является непроходимым для игрока и монстров
	virtual bool isSolid() const;
	// Может быть поднят монстрами и игроком
	virtual bool isGrabbable() const;
	// Может двигаться игроком
	virtual bool isMovable() const;
	// Проверка метки удаления объекта
	bool isRemoved() const;
	// Вызов установки метки удаления объекта
	void Remove();
	// Получение и установка координат
	int getX() const;
	int getY() const;
	void setX(float x);
	void setY(float y);
	// Получения индекса ячейки на карте для текущего положения объекта (ближайшая)
	int getCellI() const;
	int getCellJ() const;
	// Обновление объекта
	virtual void Update(float dt);
	// Проверка пересечения с другим объектом
	bool isIntersectWith(const GameObject * obj) const;
	const static int SIZE = 50; // Фиксированный размер игрового элемента
};

